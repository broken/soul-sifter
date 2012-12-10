//
//  Track.cpp
//  soul-sifter
//
//  Created by Robby Neale on 11/24/12.
//
//

#include "Track.h"

#include <iostream>

#include <cppconn/connection.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include "MysqlAccess.h"

namespace soulsifter {

Track::Track() :
id(0),
re_id(0),
artist(),
album(),
trackNum(),
title(),
remix(),
featuring(),
label(),
catalogId(),
releaseDateYear(),
releaseDateMonth(),
releaseDateDay(),
basicGenre(),
genres(0),
filePath() {
}

Track::~Track() {
    delete[] genres;
}

void Track::getTrack(Track* track) {
    try {
        sql::Connection* connection = MysqlAccess::getInstance().getConnection();
        sql::Statement* stmt = connection->createStatement();
        sql::ResultSet* result;
        if (track->id > 0) {
            result = stmt->executeQuery("select * from songs where id=" + track->id);
        } else if (track->re_id > 0) {
            result = stmt->executeQuery("select * from songs where re_id=" + track->re_id);
        }
        result->next();
        if (track->id != result->getInt("id")) {
            std::cout << "Track id updated from " << track->id << " to " << result->getInt("id") << std::endl;
            track->id = result->getInt("id");
        }
        if (track->re_id != result->getInt("re_id")) {
            std::cout << "Track re_id updated from " << track->re_id << " to " << result->getInt("re_id") << std::endl;
            track->re_id = result->getInt("re_id");
        }
        if (track->artist.compare(result->getString("artist"))) {
            std::cout << "Track artist updated from " << track->artist << " to " << result->getString("artist") << std::endl;
            track->artist = result->getString("artist");
        }
        if (track->album.compare(result->getString("album"))) {
            std::cout << "Track album updated from " << track->album << " to " << result->getString("album") << std::endl;
            track->album = result->getString("album");
        }
        if (track->trackNum.compare(result->getString("trackNum"))) {
            std::cout << "Track trackNum updated from " << track->trackNum << " to " << result->getString("trackNum") << std::endl;
            track->trackNum = result->getString("trackNum");
        }
        if (track->title.compare(result->getString("title"))) {
            std::cout << "Track title updated from " << track->title << " to " << result->getString("title") << std::endl;
            track->title = result->getString("title");
        }
        if (track->remix.compare(result->getString("remix"))) {
            std::cout << "Track remix updated from " << track->remix << " to " << result->getString("remix") << std::endl;
            track->remix = result->getString("remix");
        }
        if (track->featuring.compare(result->getString("featuring"))) {
            std::cout << "Track featuring updated from " << track->featuring << " to " << result->getString("featuring") << std::endl;
            track->featuring = result->getString("featuring");
        }
        if (track->label.compare(result->getString("label"))) {
            std::cout << "Track label updated from " << track->label << " to " << result->getString("label") << std::endl;
            track->label = result->getString("label");
        }
        if (track->catalogId.compare(result->getString("catalogId"))) {
            std::cout << "Track catalogId updated from " << track->catalogId << " to " << result->getString("catalogId") << std::endl;
            track->catalogId = result->getString("catalogId");
        }
        if (track->releaseDateYear.compare(result->getString("releaseDateYear"))) {
            std::cout << "Track releaseDateYear updated from " << track->releaseDateYear << " to " << result->getString("releaseDateYear") << std::endl;
            track->releaseDateYear = result->getString("releaseDateYear");
        }
        if (track->releaseDateMonth.compare(result->getString("releaseDateMonth"))) {
            std::cout << "Track releaseDateMonth updated from " << track->releaseDateMonth << " to " << result->getString("releaseDateMonth") << std::endl;
            track->releaseDateMonth = result->getString("releaseDateMonth");
        }
        if (track->releaseDateDay.compare(result->getString("releaseDateDay"))) {
            std::cout << "Track releaseDateDay updated from " << track->releaseDateDay << " to " << result->getString("releaseDateDay") << std::endl;
            track->releaseDateDay = result->getString("releaseDateDay");
        }
        if (track->basicGenre.compare(result->getString("basicGenre"))) {
            std::cout << "Track basicGenre updated from " << track->basicGenre << " to " << result->getString("basicGenre") << std::endl;
            track->basicGenre = result->getString("basicGenre");
        }
        if (track->filePath.compare(result->getString("filePath"))) {
            std::cout << "Track filePath updated from " << track->filePath << " to " << result->getString("filePath") << std::endl;
            track->filePath = result->getString("filePath");
        }
    } catch (sql::SQLException &e) {
        std::cout << "ERROR: SQLException in " << __FILE__;
        std::cout << " (" << __func__<< ") on line " << __LINE__ << std::endl;
        std::cout << "ERROR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << ")" << std::endl;
    }
}

}