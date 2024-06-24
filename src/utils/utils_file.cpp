#include "utils_file.h"
#include "defines.h"

#include <cstdio>
#include <string>
#include <sstream>
#include <fstream>

// Public functions
/////////////////////////////////////////////////////////////////////////////////
const usizei file_get_size(std::ifstream& file) {
  file.seekg(0, file.end);
  usizei size = file.tellg();
  file.seekg(0, file.beg);

  return size;
}

const usizei file_get_size(const std::string& path) {
  std::ifstream file(path);
  return file_get_size(file);
}

bool file_read_string(const std::ifstream& file, std::string* out_str) {
  std::stringstream ss;
  
  if(!file.is_open()) {
    fprintf(stderr, "[ERROR]: Cannot read non-opened file\n");
    return false;
  }

  ss << file.rdbuf();
  *out_str = ss.str();
  
  return true;
}

bool file_read_string(const std::string& path, std::string* out_str) {
  std::ifstream file(path);
  bool read = file_read_string(file, out_str);

  file.close();
  return read;
}

bool file_read_binary(std::ifstream& file, void* out_buff, const usizei buff_size) {
  if(!file.is_open()) {
    fprintf(stderr, "[ERROR]: Cannot read non-opened file\n");
    return false;
  }

  if(!out_buff) {
    return false;
  }
   
  file.read((char*)out_buff, buff_size);
  return true;
}

bool file_read_binary(const std::string& path, void* out_buff, const usizei buff_size) {
  std::ifstream file(path, std::ios::binary);
  bool read = file_read_binary(file, out_buff, buff_size);
  
  file.close();
  return read;
}

bool file_write_string(std::ofstream& file, const std::string& contents) {
  if(!file.is_open()) {
    fprintf(stderr, "[ERROR]: Cannot read non-opened file\n");
    return false;
  }

  file << contents;
  return true;
}

bool file_write_string(const std::string& path, const std::string& contents) {
  std::ofstream file(path);
  bool wrote = file_write_string(file, contents);

  file.close();
  return wrote;
}

bool file_write_binary(std::ofstream& file, const void* in_buff, const usizei buff_size) {
  if(!file.is_open()) {
    fprintf(stderr, "[ERROR]: Cannot read non-opened file\n");
    return false;
  }

  if(!in_buff) {
    return false;
  }

  file.write((char*)in_buff, buff_size);
  return true;
}

bool file_write_binary(const std::string& path, const void* in_buff, const usizei buff_size) {
  std::ofstream file(path, std::ios::binary);
  bool wrote = file_write_binary(file, in_buff, buff_size);

  file.close();
  return wrote;
}
/////////////////////////////////////////////////////////////////////////////////
