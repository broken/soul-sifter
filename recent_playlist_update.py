#!/usr/bin/env python

from gmusicapi.api import Api
from getpass import getpass
from argparse import ArgumentParser

parser = ArgumentParser(description='Create/Update a most recent songs playlist in Google Music.')
parser.add_argument("email", help="Google Music login email", metavar="EMAIL")
parser.add_argument("password", help="Google Music app password", metavar="PASSWORD")
parser.add_argument("-s", "--playlist_size", default=100, type=int, dest="playlist_size", help="Number of most recent songs to update playlist", metavar="NUM")
parser.add_argument("-n", "--playlist_name", default="Recent", dest="playlist_name", help="Name of playlist to update/create", metavar="NAME")
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

def main():
    """Demonstrates some api features."""

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
 
    # find most recent songs
    library.sort(key=lambda s: s["creationDate"], reverse=True)
    playlist_songs = library[0:args.playlist_size]
        
    # find playlist
    playlists = api.get_all_playlist_ids(auto=False, user=True)
    playlist_id = 0
    for playlist in playlists:
        if (playlist[0] is args.playlist_name):
            print "Found {} playlist.".format(args.playlist_name)
            playlist_id = playlist[1]
            break
    if (playlist_id == 0):
        print "Creating {} playlist.".format(args.playlist_name)
        playlist_id = api.create_playlist(args.playlist_name)
    
    # update playlist
    print "Updating playlist..."
    api.change_playlist(playlist_id, playlist_songs, False)
    print "done."
    
    #It's good practice to logout when finished.
    api.logout()
    print "All done!"

if __name__ == '__main__':
    main()
