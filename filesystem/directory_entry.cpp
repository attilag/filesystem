#include "directory_entry.h"

#include "file_status.h"

#include <sys/stat.h>

#include <system_error>
#include <functional>

NAMESPACE_BEGIN(filesystem)

NAMESPACE_BEGIN(detail_)

  inline CONSTEXPR filesystem::file_type mode2file_type(mode_t m) {
    if (S_ISREG(m)) {
      return file_type::regular;
    } else if (S_ISDIR(m)) {
      return file_type::directory;
    } else if (S_ISCHR(m)) { 
      return file_type::character;
    } else if (S_ISBLK(m)) {
      return file_type::block;
    } else if (S_ISFIFO(m)) {
      return  file_type::fifo;
#ifndef _WIN32      
    } else if (S_ISLNK(m)) {
      return file_type::symlink;
    } else if (S_ISSOCK(m)) {
      return file_type::socket;
#endif // ifndef _WIN32
    }
    return file_type::unknown;
  }

  inline CONSTEXPR filesystem::perms mode2perms(mode_t m)
  {
	  return ( ( (m & S_IRUSR) ? perms::owner_read : perms::none )
	         | ( (m & S_IWUSR) ? perms::owner_write : perms::none )
	         | ( (m & S_IXUSR) ? perms::owner_exec : perms::none )
	         | ( (m & S_IRGRP) ? perms::group_read : perms::none )
	         | ( (m & S_IWGRP) ? perms::group_write : perms::none )
  	       | ( (m & S_IXGRP) ? perms::group_exec : perms::none )
	         | ( (m & S_IROTH) ? perms::others_read : perms::none )
	         | ( (m & S_IWOTH) ? perms::others_write : perms::none )
	         | ( (m & S_IXOTH) ? perms::others_exec : perms::none )
#ifndef _WIN32
  	       | ( (m & S_ISUID) ? perms::set_uid : perms::none )
	         | ( (m & S_ISGID) ? perms::set_gid : perms::none )
	         | ( (m & S_ISVTX) ? perms::sticky_bit : perms::none )
#endif // #ifdnef _WIN32
           );
  }

  inline std::error_code make_errno_ec()
	  { return std::error_code(errno, std::system_category()); }

  file_status status_(const filesystem::path& p, std::error_code& ec, std::function<int(const char*,struct stat*)> callback_stat) {
    struct stat st;
    file_status ret;

    ec.clear();

    if (callback_stat(p.str().c_str(), &st) == 0) {
      ret.type(mode2file_type(st.st_mode));
      ret.permissions(mode2perms(st.st_mode));
    } else if (errno == ENOENT) {
      ret.type(filesystem::file_type::not_found);
    } else {
      ec = make_errno_ec();
    }

    return ret;

  }

  file_status status(const filesystem::path& p, std::error_code& ec) {
    return status_(p, ec, stat);
  }

  file_status status(const filesystem::path& p) {
    std::error_code ec;
    auto ret = status(p, ec);
    // TODO(attilag): write filesystem_error #16/12/31-17:14    
    if (ec) throw std::system_error(ec, "Cloud not stat file");
    return ret;
  }

  file_status symlink_status(const filesystem::path& p, std::error_code& ec) {
#ifdef _WIN32
    return status_(p, ec, stat);
#else
    return status_(p, ec, lstat);
#endif // #ifdef _WIN32
  }

  file_status symlink_status(const filesystem::path& p) {
    std::error_code ec;
#ifdef _WIN32
    auto ret = status_(p, ec, stat);
#else
    auto ret = status_(p, ec, lstat);
#endif // #ifdef _WIN32
    if (ec) throw std::system_error(ec, "Cloud not stat file");
      return ret;
  }


NAMESPACE_END(detail_)

directory_entry::directory_entry(const class filesystem::path& p)
  : path_(p)
    { }

directory_entry::~directory_entry()
  { }

void directory_entry::assign(const class filesystem::path& path) {
  path_ = path;
}

void directory_entry::replace_filename(const class filesystem::path& path) {
  path_.replace_filename(path);
}

filesystem::file_status directory_entry::status() const {
  return detail_::status(path_);
}

filesystem::file_status directory_entry::status(std::error_code& ec) const NOEXCEPT {
  return detail_::status(path_, ec);
}

filesystem::file_status directory_entry::symlink_status() const {
  return detail_::symlink_status(path_);
}

filesystem::file_status directory_entry::symlink_status(std::error_code& ec) const NOEXCEPT {
  return detail_::symlink_status(path_, ec);
}

NAMESPACE_END(filesystem)
