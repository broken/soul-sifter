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
  
  updates = Array.new
  res = dbh.query("select id, artist, track, title, remix, filepath from songs where albumid = #{albumid}")
  res.each do |song|
    print "# for #{song['id']} - #{song['artist']} - #{song['track']} - #{song['title']} (#{song['remix']})  "
    num = STDIN.gets.to_i
    updates[num] ||= []
    updates[num] << song["id"]
  end
  
  albums = [albumid]
  (1..updates.size).each do |idx|
    next if idx == 1
    dbh.query("insert into albums (name, artist, coverfilepath, mixed, label, catalogid, releasedateyear, releasedatemonth, releasedateday, basicgenreid) values ('#{album['name']}', '#{album['artist']}', '#{album['coverfilepath']}', #{album['mixed']}, '#{album['label']}', '#{album['catalogid']}', #{album['releasedateyear']}, #{album['releasedatemonth']}, #{album['releasedateday']}, #{album['basicgenreid']});")
    albums << dbh.last_id
    puts "Duplicated album to id #{albums[idx-1]}"
  end
  
  updates.each_with_index do |ids, idx|
    dbh.query("update songs set albumid = #{albums[idx]} where id in (#{ids.join(',')})")
    print "Updated artist for album #{idx}?  "
    artist = STDIN.gets
    if (!artist.empty?)
      dbh.query("update albums set artist = '#{artist}' where id = #{albums[idx]}")
    end
  end

rescue Mysql2::Error => e
  puts "Error code: #{e.errno}"
  puts "Error message: #{e.error}"
  puts "Error SQLSTATE: #{e.sqlstate}" if e.respond_to?("sqlstate")
ensure
  dbh.close if dbh
end
