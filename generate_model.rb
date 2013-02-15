#!/usr/bin/ruby

# TODO vectors are shallow copies; need to make them deep
# TODO getter for vector
# TODO rename reXml
# TODO preset all pointers
# TODO add syncing of objects

module Attrib
  ID = 2**0  # field: an id field for another pointer field object
  FIND = 2**1  # field: add a find method for the field
  PTR = 2**2  # field: field is a pointer to the object
  SAVEID = 2**3  # class: saving the object must explicitly set id
  SAVEVEC = 2**4  # field:
  TRANSIENT = 2**5  # field: not persistent
  KEY2 = 2**6  # field: secondary key, can be multiple fields which make it up
end

def cap (x)
  if (x[0,2] == "re" && x[2,1] == x[2,1].upcase)
    return x.slice(0,2).upcase + x.slice(2..-1)
  else
    return x.slice(0,1).capitalize + x.slice(1..-1)
  end
end

def vectorGeneric (v)
  return v.match(/^vector<(const )?([^*]*)\*?\>$/).captures[1]
end

def isVector(t)
  return t =~ /^vector</
end

def single(n)
  if (n.downcase == "mixes")
    return "mix"
  elsif (n.downcase == "children")
    return "child"
  else
    return n[0..-2]
  end
end

def plural(x)
  if (x.downcase == "mix")
    return "mixes"
  elsif (x.downcase == "child")
    return "children"
  elsif (x.downcase == "rexml")
    return "reXml"
  else
    return "#{x}s"
  end
end

def writeHeader (name, fields, attribs, customMethods, customHeaders)
  capName = cap(name)
  secondaryKeys = fields.select{|f| f[2] & Attrib::KEY2 > 0 }
  str = ""
  str << "//\n//  #{capName}.h\n//  soul-sifter\n//\n//  Created by Robby Neale\n//  Generated by generate_model.rb\n//\n\n#ifndef __soul_sifter__#{capName}__\n#define __soul_sifter__#{capName}__\n\n#include <string>\n#include <vector>\n\n"
  str << customHeaders
  fields.transpose[0].uniq.each do |t|
    unless ([:int, :bool, :time_t, :string].include?(t) || isVector(t))
      str << "#include \"#{t}.h\"\n"
    end
  end
  str << "\nnamespace sql {\n    class ResultSet;\n}\n\nusing namespace std;\n\nnamespace soulsifter {\n\n"
  str << "    class #{capName} {\n    public:\n"
  str << "        #{capName}();\n        explicit #{capName}(const #{capName}& #{name});\n        void operator=(const #{capName}& #{name});\n        ~#{capName}();\n        void clear();\n\n"
  # find methods
  fields.each do |f|
    if (f[2] & Attrib::FIND > 0)
      if ([:int, :bool, :time_t].include?(f[0]))
        str << "        static #{capName}* findBy#{cap(f[1])}(#{f[0]} #{f[1]});\n"
      else
        str << "        static #{capName}* findBy#{cap(f[1])}(const #{f[0]}& #{f[1]});\n"
      end
    end
  end
  if (!secondaryKeys.empty?)
    str << "        static #{capName}* findBy"
    secondaryKeys.each_with_index do |f,idx|
      if (idx > 0)
        str << "And"
      end
      str << "#{cap(f[1])}"
    end
    str << "("
    secondaryKeys.each_with_index do |f,idx|
      if (idx > 0)
        str << ", "
      end
      if ([:int, :bool, :time_t].include?(f[0]))
        str << "#{f[0]} #{f[1]}"
      else
        str << "const #{f[0]}& #{f[1]}"
      end
    end
    str << ");\n"
  end
  str << "\n        bool sync();\n        int update();\n        int save();\n\n"
  # custom methods
  str << customMethods
  fields.each do |f|
    if ([:int, :bool, :time_t].include?(f[0]))
      str << "        const #{f[0]} get#{cap(f[1])}() const;\n"
      str << "        void set#{cap(f[1])}(#{f[0]} #{f[1]});\n"
    elsif (f[2] & Attrib::PTR > 0)
      str << "        #{f[0]}* get#{cap(f[1])}() const;\n"
      str << "        void set#{cap(f[1])}(const #{f[0]}& #{f[1]});\n"
    elsif (isVector(f[0]))
      str << "        const #{f[0]}& get#{cap(f[1])}() const;\n"
      str << "        void set#{cap(f[1])}(const #{f[0]}& #{f[1]});\n"
    else
      str << "        const #{f[0]}& get#{cap(f[1])}() const;\n"
      str << "        void set#{cap(f[1])}(const #{f[0]}& #{f[1]});\n"
    end
    if (isVector(f[0]))
      str << "        void add#{cap(single(f[1]))}(const #{vectorGeneric(f[0])}& #{single(f[1])});\n"
      str << "        void remove#{cap(single(f[1]))}(int #{single(f[1])}Id);\n"
    end
  end
  str << "\n    private:\n"
  fields.each do |f|
    str << "        #{f[0]}#{'*' if (f[2] & Attrib::PTR > 0)} #{f[1]};"
    str << "  // transient" if (f[2] & Attrib::TRANSIENT > 0)
    str << "\n"
  end
  str << "\n        static void populateFields(const sql::ResultSet* rs, #{capName}* #{name});\n    };\n\n}\n\n#endif /* defined(__soul_sifter__#{capName}__) */\n"
  return str
end

def writeCode (name, fields, attribs)
  capName = cap(name)
  secondaryKeys = fields.select{|f| f[2] & Attrib::KEY2 > 0 }
  str = ""
  str << "//\n//  #{capName}.cpp\n//  soul-sifter\n//\n//  Created by Robby Neale\n//  Generated by generate_model.rb\n//\n\n#include \"#{capName}.h\"\n\n#include <string>\n\n#include <cppconn/connection.h>\n#include <cppconn/statement.h>\n#include <cppconn/prepared_statement.h>\n#include <cppconn/resultset.h>\n#include <cppconn/exception.h>\n#include <cppconn/warning.h>\n\n#include \"MysqlAccess.h\"\n\nusing namespace std;\n\nnamespace soulsifter {\n"
  str << "\n# pragma mark initialization\n\n"
  str << "    #{capName}::#{capName}() :\n"
  fields.each do |f|
    if (f[0] == :int)
      str << "    #{f[1]}(0),\n"
    elsif (f[0] == :bool)
        str << "    #{f[1]}(false),\n"
    elsif (f[2] & Attrib::PTR > 0 || f[0] == :time_t)
        str << "    #{f[1]}(NULL),\n"
    else
        str << "    #{f[1]}(),\n"
    end
  end
  str = str[0..-3]
  str << " {\n    }\n\n"
  str << "    #{capName}::#{capName}(const #{capName}& #{name}) :\n"
  fields.each do |f|
    if (f[2] & Attrib::PTR > 0)
      str << "    #{f[1]}(NULL),\n"
    elsif (isVector(f[0]))
      str << "    #{f[1]}(),\n"
    else
      str << "    #{f[1]}(#{name}.get#{cap(f[1])}()),\n"
    end
  end
  str = str[0..-3]
  str << " {\n"
  fields.each do |f|
    if (isVector(f[0]))
      str << "        #{f[1]} = #{name}.get#{cap(f[1])}();\n"
    end
  end
  str << "    }\n\n"
  str << "    void #{capName}::operator=(const #{capName}& #{name}) {\n"
  fields.each do |f|
    if (f[2] & Attrib::PTR > 0)
      str << "        #{f[1]} = NULL;\n"
    else
      str << "        #{f[1]} = #{name}.get#{cap(f[1])}();\n"
    end
  end
  str << "    }\n\n"
  str << "    #{capName}::~#{capName}() {\n"
  fields.each do |f|
    if (f[2] & Attrib::PTR > 0)
      str << "        delete #{f[1]};\n"
      str << "        #{f[1]} = NULL;\n"
    elsif (isVector(f[0]))
      str << "        while (!#{f[1]}.empty()) delete #{f[1]}.back(), #{f[1]}.pop_back();\n"
    end
  end
  str << "    }\n\n"
  str << "    void #{capName}::clear() {\n"
  fields.each do |f|
    if (f[0] == :int || f[0] == :time_t)
      str << "        #{f[1]} = 0;\n"
    elsif (f[0] == :string)
      str << "        #{f[1]}.clear();\n"
    elsif (f[0] == :bool)
      str << "        #{f[1]} = false;\n"
    elsif (f[2] & Attrib::PTR > 0)
      str << "        delete #{f[1]};\n"
      str << "        #{f[1]} = NULL;\n"
    elsif (isVector(f[0]))
      str << "        for (#{f[0]}::iterator it = #{f[1]}.begin(); it != #{f[1]}.end(); ++it) {\n            delete *it;\n        }\n        #{f[1]}.clear();\n"
    else
      str << "        // TODO #{f[1]}\n"
    end
  end
  str << "    }\n\n"
  str << "# pragma mark static methods\n\n"
  str << "    void #{capName}::populateFields(const sql::ResultSet* rs, #{capName}* #{name}) {\n"
  fields.each do |f|
    next if (f[2] & Attrib::PTR > 0 || f[2] & Attrib::TRANSIENT > 0)
    if (f[0] == :bool)
      str << "        #{name}->set#{cap(f[1])}(rs->getBoolean(\"#{f[1]}\"));\n"
    elsif (isVector(f[0]))
      str << "        // TODO set #{f[1]}\n"
    elsif (f[0] == :time_t)
      str << "        #{name}->set#{cap(f[1])}(timeFromString(rs->getString(\"#{f[1]}\")));\n"
    else
      str << "        #{name}->set#{cap(f[1])}(rs->get#{cap(f[0].to_s)}(\"#{f[1]}\"));\n"
    end
  end
  str << "    }\n\n"
  # find methods
  fields.each do |f|
    if (f[2] & Attrib::FIND > 0)
      if ([:int, :bool, :time_t].include?(f[0]))
        str << "    #{capName}* #{capName}::findBy#{cap(f[1])}(#{f[0]} #{f[1]}) {\n"
      else
        str << "    #{capName}* #{capName}::findBy#{cap(f[1])}(const #{f[0]}& #{f[1]}) {\n"
      end
      str << "        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement(\"select * from #{cap(plural(name))} where #{f[1]} = ?\");\n"
      str << "        ps->set#{cap(f[0].to_s)}(1, #{f[1]});\n        sql::ResultSet *rs = ps->executeQuery();\n        #{capName} *#{name} = NULL;\n        if (rs->next()) {\n            #{name} = new #{capName}();\n            populateFields(rs, #{name});\n        }\n        rs->close();\n        delete rs;\n\n        return #{name};\n    }\n\n"
    end
  end
  if (!secondaryKeys.empty?)
    str << "    #{capName}* #{capName}::findBy"
    secondaryKeys.each_with_index do |f,idx|
      if (idx > 0)
        str << "And"
      end
      str << "#{cap(f[1])}"
    end
    str << "("
    secondaryKeys.each_with_index do |f,idx|
      if (idx > 0)
        str << ", "
      end
      if ([:int, :bool, :time_t].include?(f[0]))
        str << "#{f[0]} #{f[1]}"
      else
        str << "const #{f[0]}& #{f[1]}"
      end
    end
    str << ") {\n"
    str << "        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement(\"select * from #{cap(plural(name))} where "
    secondaryKeys.each_with_index do |f,idx|
      if (idx > 0)
        str << " and "
      end
      str << "#{f[1]} = ?"
    end
    str << "\");\n"
    secondaryKeys.each_with_index do |f,idx|
      str << "        ps->set#{cap(f[0].to_s)}(1, #{f[1]});\n"
    end
    str << "        sql::ResultSet *rs = ps->executeQuery();\n        #{capName} *#{name} = NULL;\n        if (rs->next()) {\n            #{name} = new #{capName}();\n            populateFields(rs, #{name});\n        }\n        rs->close();\n        delete rs;\n\n        return #{name};\n    }\n\n"
  end
  str << "# pragma mark persistence\n\n"
  # sync method
  str << "    bool #{capName}::sync() {\n        #{capName}* #{name} = findById(id);\n"
  if (!secondaryKeys.empty?)
    str << "        if (!#{name}) #{name} = findBy"
    secondaryKeys.each_with_index do |f,idx|
      if (idx > 0)
        str << "And"
      end
      str << "#{cap(f[1])}"
    end
    str << "("
    secondaryKeys.each_with_index do |f,idx|
      if (idx > 0)
        str << ", "
      end
      str << "#{f[1]}"
    end
    str << ");\n"
  end
  str << "        if (!#{name}) {\n            return true;\n        }\n\n        // check fields\n        bool needsUpdate = false;\n"
  fields.each do |f|
    if (f[2] & Attrib::TRANSIENT > 0)
      next
    elsif ([:int, :bool, :time_t].include?(f[0]))
      str << "        if (#{f[1]} != #{name}->get#{cap(f[1])}()) {\n            if (#{f[1]}) {\n"
      str << "                cout << \"updating #{name}'s #{f[1]} from \" << #{name}->get#{cap(f[1])}() << \" to \" << #{f[1]} << endl;\n                needsUpdate = true;\n            } else {\n"
      str << "                #{f[1]} = #{name}->get#{cap(f[1])}();\n            }\n        }\n"
    elsif (f[0] == :string)
      str << "        if (#{f[1]}.compare(#{name}->get#{cap(f[1])}())) {\n            if (!#{f[1]}.empty()) {\n"
      str << "                cout << \"updating #{name} #{f[1]} from \" << #{name}->get#{cap(f[1])}() << \" to \" << #{f[1]} << endl;\n                needsUpdate = true;\n            } else {\n"
      str << "                #{f[1]} = #{name}->get#{cap(f[1])}();\n            }\n        }\n"
    else
      next
    end
  end
  str << "        return needsUpdate;\n    }\n\n"
  str << "    int #{capName}::update() {\n        try {\n"
  fields.each do |f|
    next unless (f[2] & Attrib::PTR > 0)
    str << "            if (#{f[1]} && #{f[1]}->sync()) {\n                #{f[1]}->update();\n            }\n"
  end
  str << "            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement(\"update #{cap(plural(name))} set "
  fields.each do |f|
    next if (f[1] == "id" || f[2] & Attrib::PTR > 0 || isVector(f[0]) || f[2] & Attrib::TRANSIENT > 0)
    str << "#{f[1]}=?, "
  end
  str = str[0..-3]  
  str << " where id=?\");\n"
  i = 0
  fields.each do |f|
    next if (f[1] == "id" || f[2] & Attrib::PTR > 0 || isVector(f[0]) || f[2] & Attrib::TRANSIENT > 0)
    i += 1
    if (f[0] == :bool)
      str << "            ps->setBoolean(#{i}, #{f[1]});\n"
    elsif (f[0] == :time_t)
      str << "            ps->setString(#{i}, stringFromTime(#{f[1]}));\n"
    else
      str << "            ps->set#{cap(f[0].to_s)}(#{i}, #{f[1]});\n"
    end
  end
  str << "            ps->setInt(#{i + 1}, id);\n            return ps->executeUpdate();\n"
  str << "        } catch (sql::SQLException &e) {\n            cerr << \"ERROR: SQLException in \" << __FILE__;\n            cerr << \" (\" << __func__<< \") on line \" << __LINE__ << endl;\n            cerr << \"ERROR: \" << e.what();\n            cerr << \" (MySQL error code: \" << e.getErrorCode();\n            cerr << \", SQLState: \" << e.getSQLState() << \")\" << endl;\n            return 0;\n        }\n    }\n\n"
  str << "    int #{capName}::save() {\n        try {\n"
  if (attribs & Attrib::SAVEID > 0)
    str << "            if (id == 0) {\n                sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement(\"select max(id) from #{cap(plural(name))}\");\n                sql::ResultSet *rs = ps->executeQuery();\n                rs->next();\n                id = rs->getInt(1) + 1;\n                rs->close();\n                delete rs;\n            }\n"
  end
  fields.each do |f|
    next unless (f[2] & Attrib::PTR > 0)
    str << "            if (#{f[1]} && (!#{f[1]}->getId() || !#{cap(f[0])}::findById(#{f[1]}->getId()))) {\n"
    str << "                if (#{f[1]}->save()) {\n"
    str << "                    if (#{f[1]}->getId()) {\n"
    str << "                        #{f[1]}Id = #{f[1]}->getId();\n"
    str << "                    } else {\n"
    str << "                        #{f[1]}Id = MysqlAccess::getInstance().getLastInsertId();\n                        #{f[1]}->setId(#{f[1]}Id);\n                    }\n"
    str << "                } else {\n"
    str << "                    cerr << \"Unable to save #{f[1]}\" << endl;\n                }\n            }\n"
  end
  str << "            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement(\"insert into #{cap(plural(name))} ("
  i = 0
  fields.each do |f|
    next if ((f[1] == "id" && attribs & Attrib::SAVEID == 0) || f[2] & Attrib::PTR > 0 || isVector(f[0]) || f[2] & Attrib::TRANSIENT > 0)
    i += 1
    str << "#{f[1]}, "
  end
  str = str[0..-3]
  str << ") values ("
  (1..i-1).each do
    str << "?, "
  end
  str << "?)\");\n"
  i = 0
  fields.each do |f|
    next if ((f[1] == "id" && attribs & Attrib::SAVEID == 0) || f[2] & Attrib::PTR > 0 || isVector(f[0]) || f[2] & Attrib::TRANSIENT > 0)
    i += 1
    if (f[0] == :bool)
      str << "            ps->set#{cap(f[0].to_s)}ean(#{i}, #{f[1]});\n"
    elsif (f[0] == :time_t)
      str << "            ps->setString(#{i}, stringFromTime(#{f[1]}));\n"
    else
      str << "            ps->set#{cap(f[0].to_s)}(#{i}, #{f[1]});\n"
    end
  end
  if (attribs & Attrib::SAVEVEC == 0)
    str << "            return ps->executeUpdate();\n"
  else
    str << "            int saved = ps->executeUpdate();\n            if (!saved) {\n"
    str << "                cerr << \"Not able to save #{name}\" << endl;\n                return 0;\n"
    str << "            } else {\n"
    str << "                const int id = MysqlAccess::getInstance().getLastInsertId();\n                if (id == 0) {\n"
    str << "                    cerr << \"Inserted #{name}, but unable to retreive inserted ID.\" << endl;\n                    return 0;\n                }\n"
    str << "                sql::PreparedStatement *ps;\n"
    fields.each do |f|
      if (isVector(f[0]))
        str << "                ps = MysqlAccess::getInstance().getPreparedStatement(\"insert into #{capName}#{cap(f[1])} (#{name}Id, #{single(f[1])}Id) values (?, ?)\");\n                for (#{f[0]}::iterator it = #{f[1]}.begin(); it != #{f[1]}.end(); ++it) {\n"
        str << "                    ps->setInt(1, id);\n                    ps->setInt(2, (*it)->getId());\n                    if (!ps->executeUpdate()) {\n                        cerr << \"Did not save #{single(f[1])} for #{name}\" << endl;\n                    }\n                }\n"
      end
    end
    str << "                return 1;\n            }\n"
  end
  str << "        } catch (sql::SQLException &e) {\n            cerr << \"ERROR: SQLException in \" << __FILE__;\n            cerr << \" (\" << __func__<< \") on line \" << __LINE__ << endl;\n            cerr << \"ERROR: \" << e.what();\n            cerr << \" (MySQL error code: \" << e.getErrorCode();\n            cerr << \", SQLState: \" << e.getSQLState() << \")\" << endl;\n            return 0;\n        }\n    }\n\n"
  str << "\n# pragma mark accessors\n\n"
  fields.each do |f|
    if (f[0] == :string)
      str << "    const string& #{capName}::get#{cap(f[1])}() const { return #{f[1]}; }\n"
      str << "    void #{capName}::set#{cap(f[1])}(const string& #{f[1]}) { this->#{f[1]} = #{f[1]}; }\n"
    elsif (f[2] & Attrib::PTR > 0)
      str << "    #{f[0]}* #{capName}::get#{cap(f[1])}() const {\n        if (!#{f[1]} && #{f[1]}Id)\n            return #{f[0][0..-1]}::findById(#{f[1]}Id);\n        return #{f[1]};\n    }\n"
      str << "    void #{capName}::set#{cap(f[1])}(const #{f[0]}& #{f[1]}) {\n        this->#{f[1]}Id = #{f[1]}.getId();\n        delete this->#{f[1]};\n        this->#{f[1]} = new #{f[0]}(#{f[1]});\n    }\n"
    elsif (isVector(f[0]))
      str << "    const #{f[0]}& #{capName}::get#{cap(f[1])}() const { return #{f[1]}; }\n"
      str << "    void #{capName}::set#{cap(f[1])}(const #{f[0]}& #{f[1]}) { this->#{f[1]} = #{f[1]}; }\n"
    else
      str << "    const #{f[0]} #{capName}::get#{cap(f[1])}() const { return #{f[1]}; }\n"
      if (f[0] == :int && f[1] =~ /Id$/ && f[2] & Attrib::ID > 0)
        str << "    void #{capName}::set#{cap(f[1])}(const #{f[0]} #{f[1]}) {\n        this->#{f[1]} = #{f[1]};\n        delete #{f[1][0..-3]};\n        #{f[1][0..-3]} = NULL;\n    }\n"
      else
        str << "    void #{capName}::set#{cap(f[1])}(const #{f[0]} #{f[1]}) { this->#{f[1]} = #{f[1]}; }\n"
      end
    end
    if (isVector(f[0]))
      str << "    void #{capName}::add#{cap(single(f[1]))}(const #{vectorGeneric(f[0])}& #{single(f[1])}) { #{f[1]}.push_back(new #{cap(vectorGeneric(f[0]))}(#{single(f[1])})); }\n"
      str << "    void #{capName}::remove#{cap(single(f[1]))}(int #{single(f[1])}Id) {\n        for (#{f[0]}::iterator it = #{f[1]}.begin(); it != #{f[1]}.end(); ++it) {\n            if (#{single(f[1])}Id == (*it)->getId()) {\n                #{f[1]}.erase(it);\n            }\n        }\n    }\n"
    end
    str << "\n"
  end
  str << "}\n"
  return str
end

albumFields = [
  [:int, "id", Attrib::FIND],
  [:string, "name", Attrib::KEY2],
  [:string, "artist", Attrib::KEY2],
  [:string, "coverFilepath", Attrib::FIND],
  [:bool, "mixed", 0],
  [:string, "label", 0],
  [:string, "catalogId", 0],
  [:int, "releaseDateYear", 0],
  [:int, "releaseDateMonth", 0],
  [:int, "releaseDateDay", 0],
  [:int, "basicGenreId", Attrib::ID],
  ["BasicGenre", "basicGenre", Attrib::PTR],
]
albumCustomMethods = "        const string reReleaseDate() const;\n\n"
basicGenreFields = [
  [:int, "id", Attrib::FIND],
  [:string, "name", Attrib::KEY2],
]
basicGenreAttribs = 0
basicGenreCustomMethods = "        static const BasicGenre* findByFilepath(const string& filepath);\n        static void findAll(const vector<const BasicGenre*>** genresPtr);\n\n"
mixFields = [
  [:int, "id", Attrib::FIND],
  [:int, "outSongId", Attrib::ID],
  ["Song", "outSong", Attrib::PTR],
  [:int, "inSongId", Attrib::ID],
  ["Song", "inSong", Attrib::PTR],
  [:string, "bpmDiff", 0],
  [:int, "rank", 0],
  [:string, "comments", 0],
  [:bool, "addon", 0],
]
mixAttribs = 0
mixCustomMethods = "        friend class RapidEvolutionDatabaseMixoutsMixoutHandler;\n\n        class MixResultSet {\n        public:\n            explicit MixResultSet(sql::ResultSet* resultset);\n            ~MixResultSet();\n\n            bool next(Mix* mix);\n\n        private:\n            sql::ResultSet* rs;\n\n            MixResultSet();\n        };\n\n        static Mix* findBySongIds(const int outSongId, const int inSongId);\n        static MixResultSet* findAll();\n\n"
reSongFields = [
  [:int, "id", Attrib::FIND],
  [:string, "songidWinfo", 0],
  [:string, "songid", Attrib::FIND],
  [:string, "shortid", 0],
  [:string, "shortidWinfo", 0],
  [:string, "artist", 0],
  [:string, "album", 0],
  [:string, "track", 0],
  [:string, "title", 0],
  [:string, "time", 0],
  [:string, "timeSignature", 0],
  [:string, "filename", 0],
  [:string, "digitalOnly", 0],
  [:string, "compilation", 0],
  [:string, "keyStart", 0],
  [:int, "keyAccuracy", 0],
  [:string, "bpmStart", 0],
  [:int, "bpmAccuracy", 0],
  [:int, "rating", 0],
  [:string, "dateAdded", 0],
  [:string, "catalogId", 0],  # custom 4
  [:string, "label", 0],  # custom 3
  [:string, "remix", 0],
  [:int, "numPlays", 0],
  [:string, "comments", 0],
  [:string, "releaseDate", 0],  # custom 2
  [:string, "featuring", 0],  # custom 1
  [:string, "keyEnd", 0],
  [:string, "disabled", 0],
  [:string, "bpmEnd", 0],
  [:int, "beatIntensity", 0],
  [:string, "replayGain", 0],
  [:string, "stylesBitmask", Attrib::TRANSIENT],
]
reSongAttribs = Attrib::SAVEID
reSongCustomMethods = "        friend class RapidEvolutionDatabaseSongsSongHandler;\n\n        class RESongIterator {\n        public:\n            explicit RESongIterator(sql::ResultSet* resultset);\n            ~RESongIterator();\n\n            bool next(RESong* song);\n            const int getMixoutCountForCurrentSong() const;\n\n        private:\n            sql::ResultSet* rs;\n            int mixoutCount;\n\n            RESongIterator();\n        };\n\n        static RESongIterator* findAll();\n        static const int maxREId();\n        void getStylesFromBitmask(vector<Style*>** styles);\n        void setStylesBitmaskFromDb();\n        void setStylesBitmask(const vector<Style*>& styles);\n\n"
reSongCustomHeaders = "#include \"Style.h\"\n"
songFields = [
  [:int, "id", Attrib::FIND],
  [:string, "artist", 0],
  [:string, "track", 0],
  [:string, "title", 0],
  [:string, "remix", 0],
  [:string, "featuring", 0],
  [:string, "filepath", 0],
  [:int, "rating", 0],
  [:time_t, "dateAdded", 0],
  [:string, "comments", 0],
  [:bool, "trashed", 0],
  [:int, "reSongId", Attrib::KEY2 | Attrib::ID],
  ["RESong", "reSong", Attrib::PTR],
  [:int, "albumId", Attrib::ID],
  ["Album", "album", Attrib::PTR],
  ["vector<Style*>", "styles", 0],
]
songAttribs = Attrib::SAVEVEC
songCustomMethods = "        explicit Song(RESong* song);\n\n        static void findSongsByStyle(const Style& style, vector<Song*>** songsPtr);\n        static RESong* createRESongFromSong(const Song& song);\n\n        const string reAlbum() const;\n        const string getDateAddedString() const;\n        void setDateAddedToNow();\n\n"
songCustomHeaders = "#include \"Style.h\"\n"
styleFields = [
  [:int, "id", Attrib::FIND],
  [:string, "name", 0],
  [:int, "reId", Attrib::FIND],
  [:string, "reLabel", 0],
  ["vector<Style*>", "children", 0],
  ["vector<Style*>", "parents", 0],
]
styleAttribs = 0
styleCustomMethods = "        bool operator<(const Style& style) const;\n        bool operator>(const Style& style) const;\n\n        static void findAll(vector<Style*>** stylesPtr);\n        static void findAllSorted(vector<Style*>** stylesPtr);\n\n"
styleCustomHeaders = ""
reSettingFields = [
  [:int, "id", Attrib::FIND],
  [:string, "name", Attrib::KEY2],
  [:string, "value", 0],
]
reSettingAttribs = 0
reSettingCustomMethods = "        static void findAll(vector<const RESetting*>* settings);\n\n        string& getValueRef();\n\n"
reSettingCustomHeaders = ""
reXmlFields = [
  [:int, "id", Attrib::FIND],
  [:string, "name", Attrib::KEY2],
  [:string, "xml", 0],
]
reXmlAttribs = 0
reXmlCustomMethods = "        string& getXmlRef();\n\n"
reXmlCustomHeaders = ""
reAlbumCoverFields = [
  [:int, "id", Attrib::FIND],
  [:string, "reId", Attrib::KEY2],
  [:string, "thumbnail", 0],
]
reAlbumCoverAttribs = 0
reAlbumCoverCustomMethods = "        class REAlbumCoverIterator {\n        public:\n            explicit REAlbumCoverIterator(sql::ResultSet* resultset);\n            ~REAlbumCoverIterator();\n\n            bool next(REAlbumCover* albumcover);\n\n        private:\n            sql::ResultSet* rs;\n\n            REAlbumCoverIterator();\n        };\n\n        static REAlbumCoverIterator* findAll();\n\n"
reAlbumCoverCustomHeaders = ""

output = File.open("soul-sifter/Album.h", "w")
output << writeHeader("album", albumFields, 0, albumCustomMethods, "")
output.close
output = File.open("soul-sifter/Album.cpp", "w")
output << writeCode("album", albumFields, 0)
output.close
output = File.open("soul-sifter/BasicGenre.h", "w")
output << writeHeader("basicGenre", basicGenreFields, basicGenreAttribs, basicGenreCustomMethods, "")
output.close
output = File.open("soul-sifter/BasicGenre.cpp", "w")
output << writeCode("basicGenre", basicGenreFields, basicGenreAttribs)
output.close
output = File.open("soul-sifter/Mix.h", "w")
output << writeHeader("mix", mixFields, mixAttribs, mixCustomMethods, "")
output.close
output = File.open("soul-sifter/Mix.cpp", "w")
output << writeCode("mix", mixFields, mixAttribs)
output.close
output = File.open("soul-sifter/RESong.h", "w")
output << writeHeader("reSong", reSongFields, reSongAttribs, reSongCustomMethods, reSongCustomHeaders)
output.close
output = File.open("soul-sifter/RESong.cpp", "w")
output << writeCode("reSong", reSongFields, reSongAttribs)
output.close
output = File.open("soul-sifter/Song.h", "w")
output << writeHeader("song", songFields, songAttribs, songCustomMethods, songCustomHeaders)
output.close
output = File.open("soul-sifter/Song.cpp", "w")
output << writeCode("song", songFields, songAttribs)
output.close
output = File.open("soul-sifter/Style.h", "w")
output << writeHeader("style", styleFields, styleAttribs, styleCustomMethods, styleCustomHeaders)
output.close
output = File.open("soul-sifter/Style.cpp", "w")
output << writeCode("style", styleFields, styleAttribs)
output.close
output = File.open("soul-sifter/RESetting.h", "w")
output << writeHeader("reSetting", reSettingFields, reSettingAttribs, reSettingCustomMethods, reSettingCustomHeaders)
output.close
output = File.open("soul-sifter/RESetting.cpp", "w")
output << writeCode("reSetting", reSettingFields, reSettingAttribs)
output.close
output = File.open("soul-sifter/REXML.h", "w")
output << writeHeader("reXml", reXmlFields, reXmlAttribs, reXmlCustomMethods, reXmlCustomHeaders)
output.close
output = File.open("soul-sifter/REXML.cpp", "w")
output << writeCode("reXml", reXmlFields, reXmlAttribs)
output.close
output = File.open("soul-sifter/REAlbumCover.h", "w")
output << writeHeader("reAlbumCover", reAlbumCoverFields, reAlbumCoverAttribs, reAlbumCoverCustomMethods, reAlbumCoverCustomHeaders)
output.close
output = File.open("soul-sifter/REAlbumCover.cpp", "w")
output << writeCode("reAlbumCover", reAlbumCoverFields, reAlbumCoverAttribs)
output.close
