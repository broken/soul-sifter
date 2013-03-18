#!/usr/bin/ruby
#
# Usage:
#   ruby -rubygems fix_sharing_album.rb <album id>

require "mysql2"

albumid = ARGV[0]
abort("Usage: ruby -rubygems fix_sharing_album.rb <albumId>") unless albumid

begin
  dbh = Mysql2::Client.new(:host => "localhost", :username => "ss", :password => "pw", :database => "music")
  
  res = dbh.query("select name, artist, coverfilepath, mixed, label, catalogid, releasedateyear, releasedatemonth, releasedateday, basicgenreid from albums where id = #{albumid};")
  for album in res
    puts "Album:  #{album['artist']} - #{album['name']}"
  end
  
  res = dbh.query("select id, artist, track, title, remix, filepath from songs where albumid = #{albumid}")
  puts "Songs: "
  res.each do |song|
    puts "   #{song['id']} - #{song['artist']} - #{song['track']} - #{song['title']} (#{song['remix']})"
  end
  
  puts "Album: #{album['artist']} - #{album['name']}"
  
  artists = Array.new
  updates = Array.new
  last_song_id = -1
  last_idx = -1
  res = dbh.query("select id, artist, track, title, remix, filepath from songs where albumid = #{albumid}")
  res.each do |song|
    last_idx += 1 unless (song['id'] - last_song_id == 1)
    print "# for #{song['id']} - #{song['artist']} - #{song['track']} - #{song['title']} (#{song['remix']}).. #{last_idx}?  "
    last_song_id = song['id']
    num = STDIN.gets.chomp!
    last_idx = num.to_i unless (num.empty?)
    updates[last_idx] ||= []
    updates[last_idx] << song["id"]
    if (artists[last_idx].nil?)
      artists[last_idx] = song["artist"]
    elsif (artists[last_idx] != song["artist"])
      artists[last_idx] = ""
    end
  end
  
  albums = [albumid]
  (1..updates.size).each do |idx|
    next if idx == 1
    dbh.query("insert into albums (name, artist, coverfilepath, mixed, label, catalogid, releasedateyear, releasedatemonth, releasedateday, basicgenreid) values ('#{dbh.escape(album['name'])}', '#{dbh.escape(album['artist'])}', '#{dbh.escape(album['coverfilepath'])}', #{album['mixed']}, '#{dbh.escape(album['label'])}', '#{dbh.escape(album['catalogid'])}', #{album['releasedateyear']}, #{album['releasedatemonth']}, #{album['releasedateday']}, #{album['basicgenreid']});")
    albums << dbh.last_id
    puts "Duplicated album to id #{albums[idx-1]}"
  end
  
  updates.each_with_index do |ids, idx|
    dbh.query("update songs set albumid = #{albums[idx]} where id in (#{ids.join(',')})")
    print "Updated artist for album #{idx}.. #{artists[idx]}?  "
    artist = STDIN.gets.chomp!
    artist = artists[idx] if artist.empty?
    if (!artist.empty?)
      dbh.query("update albums set artist = '#{dbh.escape(artist)}' where id = #{albums[idx]}")
    end
  end

rescue Mysql2::Error => e
  puts "Error code: #{e.errno}"
  puts "Error message: #{e.error}"
  puts "Error SQLSTATE: #{e.sqlstate}" if e.respond_to?("sqlstate")
ensure
  dbh.close if dbh
end
