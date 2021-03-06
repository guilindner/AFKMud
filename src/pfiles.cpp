/****************************************************************************
 *                   ^     +----- |  / ^     ^ |     | +-\                  *
 *                  / \    |      | /  |\   /| |     | |  \                 *
 *                 /   \   +---   |<   | \ / | |     | |  |                 *
 *                /-----\  |      | \  |  v  | |     | |  /                 *
 *               /       \ |      |  \ |     | +-----+ +-/                  *
 ****************************************************************************
 * AFKMud Copyright 1997-2015 by Roger Libiez (Samson),                     *
 * Levi Beckerson (Whir), Michael Ward (Tarl), Erik Wolfe (Dwip),           *
 * Cameron Carroll (Cam), Cyberfox, Karangi, Rathian, Raine,                *
 * Xorith, and Adjani.                                                      *
 * All Rights Reserved.                                                     *
 *                                                                          *
 *                                                                          *
 * External contributions from Remcon, Quixadhal, Zarius, and many others.  *
 *                                                                          *
 * Original SMAUG 1.8b written by Thoric (Derek Snider) with Altrag,        *
 * Blodkai, Haus, Narn, Scryn, Swordbearer, Tricops, Gorog, Rennard,        *
 * Grishnakh, Fireblade, Edmond, Conran, and Nivek.                         *
 *                                                                          *
 * Original MERC 2.1 code by Hatchet, Furey, and Kahn.                      *
 *                                                                          *
 * Original DikuMUD code by: Hans Staerfeldt, Katja Nyboe, Tom Madsen,      *
 * Michael Seifert, and Sebastian Hammer.                                   *
 ****************************************************************************
 *                          Pfile Pruning Module                            *
 ****************************************************************************/

#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include "mud.h"
#include "clans.h"
#include "deity.h"
#include "objindex.h"
#include "pfiles.h"
#include "realms.h"

void prune_sales(  );
void remove_from_auth( const string & );
void save_timedata(  );

/* Globals */
time_t new_pfile_time_t;
short num_pfiles; /* Count up number of pfiles */
time_t now_time;
short deleted = 0;
short pexempt = 0;
short days = 0;

CMDF( do_pcrename )
{
    char_data *victim;
    string arg1;
    char newname[256], oldname[256];

    argument = one_argument( argument, arg1 );
    smash_tilde( argument );

    if( ch->isnpc(  ) )
        return;

    if( arg1.empty(  ) || argument.empty(  ) )
    {
        ch->print( "Syntax: rename <victim> <new name>\r\n" );
        return;
    }

    if( !check_parse_name( argument, true ) )
    {
        ch->print( "Illegal name.\r\n" );
        return;
    }

    /*
     * Just a security precaution so you don't rename someone you don't mean too --Shaddai 
     */
    if( !( victim = ch->get_char_room( arg1 ) ) )
    {
        ch->print( "That person is not in the room.\r\n" );
        return;
    }
    if( victim->isnpc(  ) )
    {
        ch->print( "You can't rename NPC's.\r\n" );
        return;
    }

    if( ch->get_trust(  ) < victim->get_trust(  ) )
    {
        ch->print( "I don't think they would like that!\r\n" );
        return;
    }
    snprintf( newname, 256, "%s%c/%s", PLAYER_DIR, tolower( argument[0] ), capitalize( argument ).c_str(  ) );
    snprintf( oldname, 256, "%s%c/%s", PLAYER_DIR, tolower( victim->pcdata->filename[0] ), capitalize( victim->pcdata->filename ) );

    if( access( newname, F_OK ) == 0 )
    {
        ch->print( "That name already exists.\r\n" );
        return;
    }

    /*
     * Have to remove the old god entry in the directories 
     */
    if( victim->is_immortal(  ) )
    {
        char godname[256];
        snprintf( godname, 256, "%s%s", GOD_DIR, capitalize( victim->pcdata->filename ) );
        remove( godname );
    }

    /*
     * Remember to change the names of the areas 
     */
    if( victim->pcdata->area )
    {
        char filename[256], newfilename[256];

        snprintf( filename, 256, "%s%s.are", BUILD_DIR, victim->name );
        snprintf( newfilename, 256, "%s%s.are", BUILD_DIR, capitalize( argument ).c_str(  ) );
        rename( filename, newfilename );
        snprintf( filename, 256, "%s%s.are.bak", BUILD_DIR, victim->name );
        snprintf( newfilename, 256, "%s%s.are.bak", BUILD_DIR, capitalize( argument ).c_str(  ) );
        rename( filename, newfilename );
    }

    /*
     * If they're in a clan/guild, remove them from the roster for it 
     */
    if( victim->pcdata->clan )
        remove_roster( victim->pcdata->clan, victim->name );

    STRFREE( victim->name );
    victim->name = STRALLOC( capitalize( argument ).c_str(  ) );
    STRFREE( victim->pcdata->filename );
    victim->pcdata->filename = STRALLOC( capitalize( argument ).c_str(  ) );
    if( remove( oldname ) )
    {
        log_printf( "Error: Couldn't delete file %s in do_rename.", oldname );
        ch->print( "Couldn't delete the old file!\r\n" );
    }

    /*
     * Time to save to force the affects to take place 
     */
    if( victim->pcdata->clan )
    {
        add_roster( victim->pcdata->clan, victim->name, victim->Class, victim->level, victim->pcdata->mkills, victim->pcdata->mdeaths );
        save_clan( victim->pcdata->clan );
    }
    victim->save(  );

    /*
     * Now lets update the wizlist 
     */
    if( victim->is_immortal(  ) )
        make_wizlist(  );
    ch->print( "Character was renamed.\r\n" );
}

void search_pfiles( char_data * ch, const char *dirname, const char *filename, int cvnum )
{
    FILE *fpChar;
    char fname[256];

    snprintf( fname, 256, "%s/%s", dirname, filename );
    if( !( fpChar = fopen( fname, "r" ) ) )
    {
        perror( fname );
        return;
    }

    for( ;; )
    {
        int vnum, counter = 1;
        bool done = false;

        char letter = fread_letter( fpChar );

        if( letter == '\0' )
        {
            log_printf( "%s: EOF encountered reading file: %s!", __func__, fname );
            break;
        }

        if( letter != '#' )
            continue;

        const char *word = ( feof( fpChar ) ? "End" : fread_word( fpChar ) );

        if( word[0] == '\0' )
        {
            log_printf( "%s: EOF encountered reading file: %s!", __func__, fname );
            word = "End";
        }

        if( !str_cmp( word, "End" ) )
            break;

        if( !str_cmp( word, "OBJECT" ) )
        {
            while( !done )
            {
                word = ( feof( fpChar ) ? "End" : fread_word( fpChar ) );

                if( word[0] == '\0' )
                {
                    log_printf( "%s: EOF encountered reading file: %s!", __func__, fname );
                    word = "End";
                }

                switch ( UPPER( word[0] ) )
                {
                    default:
                        fread_to_eol( fpChar );
                        break;

                    case 'C':
                        KEY( "Count", counter, fread_number( fpChar ) );
                        break;

                    case 'E':
                        if( !str_cmp( word, "End" ) )
                        {
                            done = true;
                            break;
                        }

                    case 'N':
                        if( !str_cmp( word, "Nest" ) )
                        {
                            fread_number( fpChar );
                            break;
                        }
                        break;

                    case 'O':
                        if( !str_cmp( word, "Ovnum" ) )
                        {
                            vnum = fread_number( fpChar );
                            if( !( get_obj_index( vnum ) ) )
                            {
                                bug( "Bad obj vnum in %s: %d", __func__, vnum );
                            }
                            else
                            {
                                if( vnum == cvnum )
                                    ch->pagerf( "Player %s: Counted %d of Vnum %d.\r\n", filename, counter, cvnum );
                            }
                        }
                        break;
                }
            }
        }
    }
    FCLOSE( fpChar );
}

/* Scans the pfiles to count the number of copies of a vnum being stored - Samson 1-3-99 */
void check_stored_objects( char_data * ch, int cvnum )
{
    DIR *dp;
    struct dirent *dentry;
    char directory_name[100];
    int alpha_loop;

    for( alpha_loop = 0; alpha_loop <= 25; ++alpha_loop )
    {
        snprintf( directory_name, 100, "%s%c", PLAYER_DIR, 'a' + alpha_loop );
        dp = opendir( directory_name );
        dentry = readdir( dp );
        while( dentry )
        {
            /*
             * Added by Tarl 3 Dec 02 because we are now using CVS 
             */
            if( !str_cmp( dentry->d_name, "CVS" ) )
            {
                dentry = readdir( dp );
                continue;
            }
            if( dentry->d_name[0] != '.' )
                search_pfiles( ch, directory_name, dentry->d_name, cvnum );
            dentry = readdir( dp );
        }
        closedir( dp );
    }
}

void fread_pfile( FILE * fp, time_t tdiff, const char *fname, bool count )
{
    char *name = nullptr;
    char *clan = nullptr;
    char *realm = nullptr;
    char *deity = nullptr;
    short level = 0;
    bitset < MAX_PCFLAG > pact;

    pact.reset(  );

    for( ;; )
    {
        const char *word = ( feof( fp ) ? "End" : fread_word( fp ) );

        if( word[0] == '\0' )
        {
            bug( "%s: EOF encountered reading file!", __func__ );
            word = "End";
        }

        if( !str_cmp( word, "End" ) )
            break;

        switch ( UPPER( word[0] ) )
        {
            default:   // Deliberately this way - the bug spam will kill you!
            case '*':
                fread_to_eol( fp );
                break;

            case 'C':
                KEY( "Clan", clan, fread_string( fp ) );
                break;

            case 'D':
                KEY( "Deity", deity, fread_string( fp ) );
                break;

            case 'I':
                KEY( "ImmRealm", realm, fread_string( fp ) );
                break;

            case 'N':
                KEY( "Name", name, fread_string( fp ) );
                break;

            case 'P':
                if( !str_cmp( word, "PCFlags" ) )
                {
                    flag_set( fp, pact, pc_flags );
                    break;
                }
                break;

            case 'S':
                if( !str_cmp( word, "Status" ) )
                {
                    level = fread_number( fp );
                    fread_to_eol( fp );
                    break;
                }
                break;

            case 'V':
                if( !str_cmp( word, "Version" ) )
                {
                    fread_number( fp );
                    break;
                }
                break;
        }
    }

    if( count == false && !pact.test( PCFLAG_EXEMPT ) )
    {
        if( level < 10 && tdiff > sysdata->newbie_purge )
        {
            if( unlink( fname ) == -1 )
                perror( "Unlink" );
            else
            {
                days = sysdata->newbie_purge;
                log_printf( "Player %s was deleted. Exceeded time limit of %d days.", name, days );
                remove_from_auth( name );
                if( clan != nullptr )
                {
                    clan_data *pclan = get_clan( clan );

                    if( pclan ) // Check, cause there may be nothing there for some reason.
                        remove_roster( pclan, name );
                }
                ++deleted;
                STRFREE( clan );
                STRFREE( realm );
                STRFREE( deity );
                STRFREE( name );
                return;
            }
        }

        if( level < LEVEL_IMMORTAL && tdiff > sysdata->regular_purge )
        {
            if( level < LEVEL_IMMORTAL )
            {
                if( unlink( fname ) == -1 )
                    perror( "Unlink" );
                else
                {
                    days = sysdata->regular_purge;
                    log_printf( "Player %s was deleted. Exceeded time limit of %d days.", name, days );
                    remove_from_auth( name );
                    if( clan != nullptr )
                    {
                        clan_data *pclan = get_clan( clan );

                        if( pclan ) // Check, cause there may be nothing there for some reason.
                            remove_roster( pclan, name );
                    }
                    ++deleted;
                    STRFREE( clan );
                    STRFREE( realm );
                    STRFREE( deity );
                    STRFREE( name );
                    return;
                }
            }
        }
    }

    if( pact.test( PCFLAG_EXEMPT ) || level >= LEVEL_IMMORTAL )
        ++pexempt;

    if( clan != nullptr )
    {
        clan_data *guild = get_clan( clan );

        if( guild )
            ++guild->members;
    }

    if( realm != nullptr )
    {
        realm_data *rl = get_realm( realm );

        if( rl )
            ++rl->members;
    }

    if( deity != nullptr )
    {
        deity_data *god = get_deity( deity );

        if( god )
            ++god->worshippers;
    }
    STRFREE( clan );
    STRFREE( realm );
    STRFREE( deity );
    STRFREE( name );
}

void read_pfile( const char *dirname, const char *filename, bool count )
{
    FILE *fp;
    char fname[256];
    struct stat fst;
    time_t tdiff;

    now_time = time( 0 );

    snprintf( fname, 256, "%s/%s", dirname, filename );

    if( stat( fname, &fst ) != -1 )
    {
        tdiff = ( now_time - fst.st_mtime ) / 86400;

        if( ( fp = fopen( fname, "r" ) ) != nullptr )
        {
            for( ;; )
            {
                char letter;
                const char *word;

                letter = fread_letter( fp );

                if( ( letter != '#' ) && ( !feof( fp ) ) )
                    continue;

                word = ( feof( fp ) ? "End" : fread_word( fp ) );

                if( word[0] == '\0' )
                {
                    bug( "%s: EOF encountered reading file!", __func__ );
                    word = "End";
                }

                if( !str_cmp( word, "End" ) )
                    break;

                if( !str_cmp( word, "PLAYER" ) )
                    fread_pfile( fp, tdiff, fname, count );
                else if( !str_cmp( word, "END" ) )  /* Done */
                    break;
            }
            FCLOSE( fp );
        }
    }
}

void pfile_scan( bool count )
{
    DIR *dp;
    struct dirent *dentry;
    char directory_name[100];
    deleted = 0;
    pexempt = 0;

    now_time = time( 0 );

    /*
     * Reset all clans to 0 members prior to scan - Samson 7-26-00 
     */
    list < clan_data * >::iterator cl;
    if( !count )
    {
        for( cl = clanlist.begin(  ); cl != clanlist.end(  ); ++cl )
        {
            clan_data *clan = *cl;

            clan->members = 0;
        }
    }

    /*
     * Reset all realms to 0 members prior to scan - Samson 11-08-2014
     */
    list < realm_data * >::iterator rl;
    if( !count )
    {
        for( rl = realmlist.begin(  ); rl != realmlist.end(  ); ++rl )
        {
            realm_data *realm = *rl;

            realm->members = 0;
        }
    }

    /*
     * Reset all deities to 0 worshippers prior to scan - Samson 7-26-00 
     */
    list < deity_data * >::iterator ideity;
    if( !count )
    {
        for( ideity = deitylist.begin(  ); ideity != deitylist.end(  ); ++ideity )
        {
            deity_data *deity = *ideity;

            deity->worshippers = 0;
        }
    }

    short cou = 0;
    for( short alpha_loop = 0; alpha_loop <= 25; ++alpha_loop )
    {
        snprintf( directory_name, 100, "%s%c", PLAYER_DIR, 'a' + alpha_loop );

        // log_string( directory_name ); 

        dp = opendir( directory_name );
        dentry = readdir( dp );
        while( dentry )
        {
            /*
             * Added by Tarl 3 Dec 02 because we are now using CVS 
             */
            if( !str_cmp( dentry->d_name, "CVS" ) )
            {
                dentry = readdir( dp );
                continue;
            }
            if( dentry->d_name[0] != '.' )
            {
                if( !count )
                    read_pfile( directory_name, dentry->d_name, count );
                ++cou;
            }
            dentry = readdir( dp );
        }
        closedir( dp );
    }

    if( !count )
        log_string( "Pfile cleanup completed." );
    else
        log_string( "Pfile count completed." );

    log_printf( "Total pfiles scanned: %d", cou );
    log_printf( "Total exempted pfiles: %d", pexempt );

    if( !count )
    {
        log_printf( "Total pfiles deleted: %d", deleted );
        log_printf( "Total pfiles remaining: %d", cou - deleted );
        num_pfiles = cou - deleted;
    }
    else
        num_pfiles = cou;

    if( !count )
    {
        for( cl = clanlist.begin(  ); cl != clanlist.end(  ); ++cl )
        {
            clan_data *clan = *cl;
            save_clan( clan );
        }

        for( rl = realmlist.begin(  ); rl != realmlist.end(  ); ++rl )
        {
            realm_data *realm = *rl;
            save_realm( realm );
        }

        for( ideity = deitylist.begin(  ); ideity != deitylist.end(  ); ++ideity )
        {
            deity_data *deity = *ideity;
            save_deity( deity );
        }

        verify_clans(  );
        verify_realms( );
        prune_sales(  );
    }
}

CMDF( do_pfiles )
{
    char buf[512];

    if( ch->isnpc(  ) )
    {
        ch->print( "Mobs cannot use this command!\r\n" );
        return;
    }

    if( argument.empty(  ) )
    {
        /*
         * Makes a backup copy of existing pfiles just in case - Samson 
         */
        snprintf( buf, 512, "tar -cf %spfiles.tar %s*", PLAYER_DIR, PLAYER_DIR );

        /*
         * GAH, the shell pipe won't process the command that gets pieced
         * together in the preceeding lines! God only knows why. - Samson 
         */
        if( ( system( buf ) ) )
        {
            ch->print( "An error occured while processing the system command for pfile backups. The cleanup was aborted.\r\n" );
            return;
        }

        log_printf( "Manual pfile cleanup started by %s.", ch->name );
        pfile_scan( false );
        return;
    }

    if( !str_cmp( argument, "settime" ) )
    {
        new_pfile_time_t = current_time + 86400;
        save_timedata(  );
        ch->print( "New cleanup time set for 24 hrs from now.\r\n" );
        return;
    }

    if( !str_cmp( argument, "count" ) )
    {
        log_printf( "Pfile count started by %s.", ch->name );
        pfile_scan( true );
        return;
    }
    ch->print( "Invalid argument.\r\n" );
}

void check_pfiles( time_t reset )
{
    /*
     * This only counts them up on reboot if the cleanup isn't needed - Samson 1-2-00 
     */
    if( reset == 255 && new_pfile_time_t > current_time )
    {
        reset = 0;  /* Call me paranoid, but it might be meaningful later on */
        log_string( "Counting pfiles....." );
        pfile_scan( true );
        return;
    }

    if( new_pfile_time_t <= current_time )
    {
        if( sysdata->CLEANPFILES == true )
        {
            char buf[512];

            /*
             * Makes a backup copy of existing pfiles just in case - Samson 
             */
            snprintf( buf, 512, "tar -cf %spfiles.tar %s*", PLAYER_DIR, PLAYER_DIR );

            /*
             * Would use the shell pipe for this, but alas, it requires a ch in order
             * to work, this also gets called during boot_db before the rare item checks - Samson 
             */
            if( ( system( buf ) ) )
            {
                log_string( "Error during Pfile backup. Cleanup code aborted. Skipping to rare items update." );
            }
            else
            {
                new_pfile_time_t = current_time + 86400;
                save_timedata(  );
                log_string( "Automated pfile cleanup beginning...." );
                pfile_scan( false );
            }
        }
        else
        {
            new_pfile_time_t = current_time + 86400;
            save_timedata(  );
            log_string( "Counting pfiles....." );
            pfile_scan( true );
        }
    }
}
