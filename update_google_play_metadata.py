#!/usr/bin/env python
import mysql.connector
import os
import sys

from gmusicapi.api import Api
from getpass import getpass
from argparse import ArgumentParser

parser = ArgumentParser(description='Create/Update a most recent songs playlist in Google Music.')
parser.add_argument("email", help="Google Music login email", metavar="EMAIL")
parser.add_argument("password", help="Google Music app password", metavar="PASSWORD")
#parser.add_argument("-s", "--playlist_size", default=100, type=int, dest="playlist_size", help="Number of most recent songs to update playlist", metavar="NUM")
#parser.add_argument("-n", "--playlist_name", default="Recent", dest="playlist_name", help="Name of playlist to update/create", metavar="NAME")
args = parser.parse_args()

def init():
    """Makes an instance of the api and attempts to login with it.
    Returns the authenticated api.
    """
    
    api = Api() 
    
    logged_in = False
    attempts = 0

    while not logged_in and attempts < 3:
        logged_in = api.login(args.email, args.password)
        attempts += 1

    return api
    
def findGenre(con, id):
    cursor = con.cursor()
    try:
        cursor.execute("select name from styles where id = (select max(styleid) from songstyles where songid = %s)", (id,))
        return cursor.fetchone()
    except mysql.connector.Error, e:
    	print "Error: {}".format(e)
    	sys.exit(1)
    finally:
    	cursor.close()
    
def findSong(con, song):
    cursor = con.cursor()
    first = True
    dbsong = None
    try:
    	cursor.execute("select s.id, s.title, s.artist, s.track, a.id, a.name, a.artist, a.releasedateyear from songs s join albums a on s.albumid=a.id where s.title = %s", params=(song["titleNorm"],))
    	for (sid, title, artist, track, aid, albumtitle, albumartist, releasedateyear) in cursor:
    	    if not first: return None
    	    dbsong = {'songid': sid, 'title': title, 'artist': artist, 'track': track, 'albumid': aid, 'albumtitle': albumtitle, 'albumartist': albumartist, 'year': releasedateyear}
    	    first = False
    	if (dbsong == None): return None
    	if (dbsong["albumartist"] == ''): return None
    except mysql.connector.Error, e:
    	print "Error: {}".format(e)
    	sys.exit(1)
    finally:
    	cursor.close()
    
    dbsong["genre"] = findGenre(con, dbsong["songid"])
    return dbsong
    	
def test():
    #con = mysql.connector.connect(host='localhost', user='ss', password='pw', database='music')
    #song = {'titleNorm': 'skinny love'}
    #print findSong(con, song)
    exit(1)
    pass

def main():
    """Demonstrates some api features."""
    
    # Perform any tests here before app starts
    test()

    #Make a new instance of the api and prompt the user to log in.
    api = init()

    if not api.is_authenticated():
        print "Sorry, those credentials weren't accepted."
        return

    print "Successfully logged in."
    print
    
    #Get all of the users songs.
    #library is a big list of dictionaries, each of which contains a single song.
    print "Loading library...",
    library = api.get_all_songs()
    print "done."

    print len(library), "tracks detected."
    print

    con = mysql.connector.connect(host='localhost', user='ss', password='pw', database='music')
 
    for song in library:
        s = findSong(con, song)
        
        if (s == None):
            print "Unable to find: ", song
            continue
        
        if (song["name"] == s["title"] and
            song["album"] == s["albumtitle"] and
            song["albumArtist"] == s["albumartist"] and
            song["artist"] == s["artist"] and
            song["genre"] == s["genre"] and
            song["track"] == s["track"] and
            song["year"] == s["year"]):
            continue
        
        print song["name"], " -> ", s["title"]
        print song["album"], " -> ", s["albumtitle"]
        print song["albumArtist"], " -> ", s["albumartist"]
        print song["artist"], " -> ", s["artist"]
        print song["genre"], " -> ", s["genre"]
        print song["track"], " -> ", s["track"]
        print song["year"], " -> ", s["year"]
        os.system('read -p "Press any key to continue"')
        
        song["name"] = s["title"]
        song["album"] = s["albumtitle"]
        song["albumArtist"] = s["albumartist"]
        song["artist"] = s["artist"]
        #song["composer"] = s["
        #song["disc"] = s["
        song["genre"] = s["genre"]
        #song["playCount"] = s["
        #song["totalDiscs"] = s["
        #song["totalTracks"] = s["
        song["track"] = s["track"]
        song["year"] = s["year"]
        
        api.change_song_metadata(song)
    
    #It's good practice to logout when finished.
    api.logout()
    print "All done!"

if __name__ == '__main__':
    main()
