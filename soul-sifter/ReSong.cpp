//
//  ReSong.cpp
//  soul-sifter
//
//  Created by Robby Neale on 11/24/12.
//
//

#include "ReSong.h"

#include <iostream>
#include <math.h>
#include <string>

#include <cppconn/connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <cppconn/warning.h>

#include "MysqlAccess.h"

#define EPSILON 0.0000001

using namespace std;

# pragma mark initialization

ReSong::ReSong() :
unique_id(0),
songid_winfo(),
songid(),
shortid(),
shortid_winfo(),
artist(),
album(),
track(),
title(),
time(),
time_signature(),
filename(),
digital_only(),
compilation(),
key_start(),
key_accuracy(0),
bpm_start(0),
bpm_accuracy(0),
rating(0),
date_added(),
catalog_id(),
label(),
remix(),
num_plays(0),
comments(),
release_date(),
featuring(),
key_end(),
disabled(),
bpm_end(0),
beat_intensity(0),
replay_gain(0),
album_cover() {
}

ReSong::~ReSong() {
}

void ReSong::clear() {
    unique_id = 0;
    songid_winfo.clear();
    songid.clear();
    shortid.clear();
    shortid_winfo.clear();
    artist.clear();
    album.clear();
    track.clear();
    title.clear();
    time.clear();
    time_signature.clear();
    filename.clear();
    digital_only.clear();
    compilation.clear();
    key_start.clear();
    key_accuracy = 0;
    bpm_start = 0;
    bpm_accuracy = 0;
    rating = 0;
    date_added.clear();
    catalog_id.clear();
    label.clear();
    remix.clear();
    num_plays = 0;
    comments.clear();
    release_date.clear();
    featuring.clear();
    key_end.clear();
    disabled.clear();
    bpm_end = 0;
    beat_intensity = 0;
    replay_gain = 0;
    album_cover.clear();
}

# pragma mark persistence

bool ReSong::lookup(ReSong *song) {
    try {
        // use various means to try and retrieve the song
        sql::ResultSet *result;
        if (song->songid.length() > 0) {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from resongs where songid = ?");
            ps->setString(1, song->songid);
            result = ps->executeQuery();
        } else if (song->shortid.length() > 0) {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from resongs where shortid = ?");
            ps->setString(1, song->shortid);
            result = ps->executeQuery();
        } else if (song->unique_id > 0) {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from resongs where unique_id = ?");
            ps->setInt(1, song->unique_id);
            result = ps->executeQuery();
        } else {
            cout << "Nothing to search for re song by" << endl;
            return false;
        }
        
        // did we get a unique result?
        if (!result->next()) {
            cout << "No RE song found for " << song->shortid << endl;
            return false;
        } else if (!result->isLast()) {
            cout << "Ambigious result returned for " << song->shortid << endl;
            return false;
        }
        
        // update fields
        if (song->unique_id != result->getInt("unique_id")) {
            if (song->unique_id > 0)
                cout << "updating unique_id of RE song from " << song->unique_id << " to " << result->getInt("unique_id") << endl;
            song->unique_id = result->getInt("unique_id");
        }
        if (song->songid_winfo.compare(result->getString("songid_winfo"))) {
            if (song->songid_winfo.length() > 0)
                cout << "updating songid_winfo of RE song from " << song->songid_winfo << " to " << result->getString("songid_winfo") << endl;
            song->songid_winfo = result->getString("songid_winfo");
        }
        if (song->songid.compare(result->getString("songid"))) {
            if (song->songid.length() > 0)
                cout << "updating songid of RE song from " << song->songid << " to " << result->getString("songid") << endl;
            song->songid = result->getString("songid");
        }
        if (song->shortid.compare(result->getString("shortid"))) {
            if (song->shortid.length() > 0)
                cout << "updating shortid of RE song from " << song->shortid << " to " << result->getString("shortid") << endl;
            song->shortid = result->getString("shortid");
        }
        if (song->shortid_winfo.compare(result->getString("shortid_winfo"))) {
            if (song->shortid_winfo.length() > 0)
                cout << "updating shortid_winfo of RE song from " << song->shortid_winfo << " to " << result->getString("shortid_winfo") << endl;
            song->shortid_winfo = result->getString("shortid_winfo");
        }
        if (song->artist.compare(result->getString("artist"))) {
            if (song->artist.length() > 0)
                cout << "updating artist of RE song from " << song->artist << " to " << result->getString("artist") << endl;
            song->artist = result->getString("artist");
        }
        if (song->album.compare(result->getString("album"))) {
            if (song->album.length() > 0)
                cout << "updating album of RE song from " << song->album << " to " << result->getString("album") << endl;
            song->album = result->getString("album");
        }
        if (song->track.compare(result->getString("track"))) {
            if (song->track.length() > 0)
                cout << "updating track of RE song from " << song->track << " to " << result->getString("track") << endl;
            song->track = result->getString("track");
        }
        if (song->title.compare(result->getString("title"))) {
            if (song->title.length() > 0)
                cout << "updating title of RE song from " << song->title << " to " << result->getString("title") << endl;
            song->title = result->getString("title");
        }
        if (song->time.compare(result->getString("time"))) {
            if (song->time.length() > 0)
                cout << "updating time of RE song from " << song->time << " to " << result->getString("time") << endl;
            song->time = result->getString("time");
        }
        if (song->time_signature.compare(result->getString("time_signature"))) {
            if (song->time_signature.length() > 0)
                cout << "updating time_signature of RE song from " << song->time_signature << " to " << result->getString("time_signature") << endl;
            song->time_signature = result->getString("time_signature");
        }
        if (song->filename.compare(result->getString("filename"))) {
            if (song->filename.length() > 0)
                cout << "updating filename of RE song from " << song->filename << " to " << result->getString("filename") << endl;
            song->filename = result->getString("filename");
        }
        if (song->digital_only.compare(result->getString("digital_only"))) {
            if (song->digital_only.length() > 0)
                cout << "updating digital_only of RE song from " << song->digital_only << " to " << result->getString("digital_only") << endl;
            song->digital_only = result->getString("digital_only");
        }
        if (song->compilation.compare(result->getString("compilation"))) {
            if (song->compilation.length() > 0)
                cout << "updating compilation of RE song from " << song->compilation << " to " << result->getString("compilation") << endl;
            song->compilation = result->getString("compilation");
        }
        if (song->key_start.compare(result->getString("key_start"))) {
            if (song->key_start.length() > 0)
                cout << "updating key_start of RE song from " << song->key_start << " to " << result->getString("key_start") << endl;
            song->key_start = result->getString("key_start");
        }
        if (song->key_accuracy != result->getInt("key_accuracy")) {
            if (song->key_accuracy > 0)
                cout << "updating key_accuracy of RE song from " << song->key_accuracy << " to " << result->getInt("key_accuracy") << endl;
            song->key_accuracy = result->getInt("key_accuracy");
        }
        if (fabs(song->bpm_start - result->getDouble("bpm_start")) > EPSILON) {
            if (song->bpm_start > 0)
                cout << "updating bpm_start of RE song from " << song->bpm_start << " to " << result->getDouble("bpm_start") << endl;
            song->bpm_start = result->getDouble("bpm_start");
        }
        if (song->bpm_accuracy != result->getInt("bpm_accuracy")) {
            if (song->bpm_accuracy > 0)
                cout << "updating bpm_accuracy of RE song from " << song->bpm_accuracy << " to " << result->getInt("bpm_accuracy") << endl;
            song->bpm_accuracy = result->getInt("bpm_accuracy");
        }
        if (song->rating != result->getInt("rating")) {
            if (song->rating > 0)
                cout << "updating rating of RE song from " << song->rating << " to " << result->getInt("rating") << endl;
            song->rating = result->getInt("rating");
        }
        if (song->date_added.compare(result->getString("date_added"))) {
            if (song->date_added.length() > 0)
                cout << "updating date_added of RE song from " << song->date_added << " to " << result->getString("date_added") << endl;
            song->date_added = result->getString("date_added");
        }
        if (song->catalog_id.compare(result->getString("catalog_id"))) {
            if (song->catalog_id.length() > 0)
                cout << "updating catalog_id of RE song from " << song->catalog_id << " to " << result->getString("catalog_id") << endl;
            song->catalog_id = result->getString("catalog_id");
        }
        if (song->label.compare(result->getString("label"))) {
            if (song->label.length() > 0)
                cout << "updating label of RE song from " << song->label << " to " << result->getString("label") << endl;
            song->label = result->getString("label");
        }
        if (song->remix.compare(result->getString("remix"))) {
            if (song->remix.length() > 0)
                cout << "updating remix of RE song from " << song->remix << " to " << result->getString("remix") << endl;
            song->remix = result->getString("remix");
        }
        if (song->num_plays != result->getInt("num_plays")) {
            if (song->num_plays > 0)
                cout << "updating num_plays of RE song from " << song->num_plays << " to " << result->getInt("num_plays") << endl;
            song->num_plays = result->getInt("num_plays");
        }
        if (song->comments.compare(result->getString("comments"))) {
            if (song->comments.length() > 0)
                cout << "updating comments of RE song from " << song->comments << " to " << result->getString("comments") << endl;
            song->comments = result->getString("comments");
        }
        if (song->release_date.compare(result->getString("release_date"))) {
            if (song->release_date.length() > 0)
                cout << "updating release_date of RE song from " << song->release_date << " to " << result->getString("release_date") << endl;
            song->release_date = result->getString("release_date");
        }
        if (song->featuring.compare(result->getString("featuring"))) {
            if (song->featuring.length() > 0)
                cout << "updating featuring of RE song from " << song->featuring << " to " << result->getString("featuring") << endl;
            song->featuring = result->getString("featuring");
        }
        if (song->key_end.compare(result->getString("key_end"))) {
            if (song->key_end.length() > 0)
                cout << "updating key_end of RE song from " << song->key_end << " to " << result->getString("key_end") << endl;
            song->key_end = result->getString("key_end");
        }
        if (song->disabled.compare(result->getString("disabled"))) {
            if (song->disabled.length() > 0)
                cout << "updating disabled of RE song from " << song->disabled << " to " << result->getString("disabled") << endl;
            song->disabled = result->getString("disabled");
        }
        if (fabs(song->bpm_end - result->getDouble("bpm_end")) > EPSILON) {
            if (song->bpm_end > 0)
                cout << "updating bpm_end of RE song from " << song->bpm_end << " to " << result->getDouble("bpm_end") << endl;
            song->bpm_end = result->getDouble("bpm_end");
        }
        if (song->beat_intensity != result->getInt("beat_intensity")) {
            if (song->beat_intensity > 0)
                cout << "updating beat_intensity of RE song from " << song->beat_intensity << " to " << result->getInt("beat_intensity") << endl;
            song->beat_intensity = result->getInt("beat_intensity");
        }
        if (fabs(song->replay_gain - result->getDouble("replay_gain")) > EPSILON) {
            if (song->replay_gain > 0)
                cout << "updating replay_gain of RE song from " << song->replay_gain << " to " << result->getDouble("replay_gain") << endl;
            song->replay_gain = result->getDouble("replay_gain");
        }
        if (song->album_cover.compare(result->getString("album_cover"))) {
            if (song->album_cover.length() > 0)
                cout << "updating album_cover of RE song from " << song->album_cover << " to " << result->getString("album_cover") << endl;
            song->album_cover = result->getString("album_cover");
        }
        
        // clean up
        delete result;
        
        return true;
    } catch (sql::SQLException &e) {
        std::cout << "ERROR: SQLException in " << __FILE__;
        std::cout << " (" << __func__<< ") on line " << __LINE__ << std::endl;
        std::cout << "ERROR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << ")" << std::endl;
        return false;
    }
}

bool ReSong::update() {
    try {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("update resongs set songid_winfo=?, songid=?, shortid=?, shortid_winfo=?, artist=?, album=?, track=?, title=?, time=?, time_signature=?, filename=?, digital_only=?, compilation=?, key_start=?, key_accuracy=?, bpm_start=?, bpm_accuracy=?, rating=?, date_added=?, catalog_id=?, label=?, remix=?, num_plays=?, comments=?, release_date=?, featuring=?, key_end=?, disabled=?, bpm_end=?, beat_intensity=?, replay_gain=?, album_cover=? where unique_id=?");
        ps->setString(1, songid_winfo);
        ps->setString(2, songid);
        ps->setString(3, shortid);
        ps->setString(4, shortid_winfo);
        ps->setString(5, artist);
        ps->setString(6, album);
        ps->setString(7, track);
        ps->setString(8, title);
        ps->setString(9, time);
        ps->setString(10, time_signature);
        ps->setString(11, filename);
        ps->setString(12, digital_only);
        ps->setString(13, compilation);
        ps->setString(14, key_start);
        ps->setInt(15, key_accuracy);
        ps->setDouble(16, bpm_start);
        ps->setInt(17, bpm_accuracy);
        ps->setInt(18, (int) rating);
        ps->setString(19, date_added);
        ps->setString(20, catalog_id);
        ps->setString(21, label);
        ps->setString(22, remix);
        ps->setInt(23, num_plays);
        ps->setString(24, comments);
        ps->setString(25, release_date);
        ps->setString(26, featuring);
        ps->setString(27, key_end);
        ps->setString(28, disabled);
        ps->setDouble(29, bpm_end);
        ps->setInt(30, beat_intensity);
        ps->setDouble(31, replay_gain);
        ps->setString(32, album_cover);
        ps->setInt(33, unique_id);
        ps->executeUpdate();
        return true;
	} catch (sql::SQLException &e) {
        std::cout << "ERROR: SQLException in " << __FILE__;
        std::cout << " (" << __func__<< ") on line " << __LINE__ << std::endl;
        std::cout << "ERROR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << ")" << std::endl;
        return false;
	}
}

bool ReSong::save() {
    try {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("insert into resongs (songid_winfo, songid, shortid, shortid_winfo, artist, album, track, title, time, time_signature, filename, digital_only, compilation, key_start, key_accuracy, bpm_start, bpm_accuracy, rating, date_added, catalog_id, label, remix, num_plays, comments, release_date, featuring, key_end, disabled, bpm_end, beat_intensity, replay_gain, album_cover, unique_id) values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
        ps->setString(1, songid_winfo);
        ps->setString(2, songid);
        ps->setString(3, shortid);
        ps->setString(4, shortid_winfo);
        ps->setString(5, artist);
        ps->setString(6, album);
        ps->setString(7, track);
        ps->setString(8, title);
        ps->setString(9, time);
        ps->setString(10, time_signature);
        ps->setString(11, filename);
        ps->setString(12, digital_only);
        ps->setString(13, compilation);
        ps->setString(14, key_start);
        ps->setInt(15, key_accuracy);
        ps->setDouble(16, bpm_start);
        ps->setInt(17, bpm_accuracy);
        ps->setInt(18, (int) rating);
        ps->setString(19, date_added);
        ps->setString(20, catalog_id);
        ps->setString(21, label);
        ps->setString(22, remix);
        ps->setInt(23, num_plays);
        ps->setString(24, comments);
        ps->setString(25, release_date);
        ps->setString(26, featuring);
        ps->setString(27, key_end);
        ps->setString(28, disabled);
        ps->setDouble(29, bpm_end);
        ps->setInt(30, beat_intensity);
        ps->setDouble(31, replay_gain);
        ps->setString(32, album_cover);
        ps->setInt(33, unique_id);
        return ps->executeUpdate() > 0;
	} catch (sql::SQLException &e) {
        std::cout << "ERROR: SQLException in " << __FILE__;
        std::cout << " (" << __func__<< ") on line " << __LINE__ << std::endl;
        std::cout << "ERROR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << ")" << std::endl;
        return false;
	}
}