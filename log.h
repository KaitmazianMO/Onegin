#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED

#include <stdio.h>

#define LOG_WIHTOUT_TRACE  __attribute__((no_instrument_function))

enum MSG_TYPE : char
{
    CALL = 'C',
    QUIT = 'Q',     
    DUMP = 'D',

     FATAL   = 'F',
     ERROR   = 'E',
    WARNING  = 'W',
      LOG    = 'L'
};

LOG_WIHTOUT_TRACE
const char *str_type (MSG_TYPE type);

struct Logger 
{
    const char *log_file_name;
    FILE       *file ;
    size_t      indent;
    bool        dumping;  // mode for writing multy-line messages almost without formating
};

LOG_WIHTOUT_TRACE
Logger *logger_get_instance();

LOG_WIHTOUT_TRACE
void logger_set_log_file_path (const char *path);

LOG_WIHTOUT_TRACE
void logger_message (MSG_TYPE type, const char *format_line, ...);

LOG_WIHTOUT_TRACE
void logger_message_dateiled (MSG_TYPE type, const char *file, 
    const char *func, size_t line, const char *format_line, ...);
#define LOG_MSG( type, ... ) \
logger_message_dateiled (type, __FILE__, __func__, __LINE__, __VA_ARGS__);

LOG_WIHTOUT_TRACE
void logger_indent_dec();

LOG_WIHTOUT_TRACE
void logger_indent_inc();
    //struct Dumper
    //{
    //    __attribute__((no_instrument_function))
    //    Dumper (const char *dump_title)
    //    {
    //        get_instance().dumping = true;
    //        Logger::get_instance().message (DUMP, dump_title);
    //    } 
//
    //    //__attribute__((no_instrument_function))
    //    //template <typename ...Args>
    //    //void print_line (const char *format_line, Args... args)
    //    //{
    //    //    fprintf (file, "%*.s", 4*get_instance().indent, ""); // printing 4*indent spaces
    //    //    fpritnf (format_line, args...);
    //    //    fputc ('\n', file);            
    //    //}   
//
    //    __attribute__((no_instrument_function))
    //   ~Dumper()
    //    {
    //        get_instance().dumping = false;
    //    }            
    //};
//
    //__attribute__((no_instrument_function))
    //size_t indent_inc() { return indent++; }
    //__attribute__((no_instrument_function))
    //size_t indent_dec() { return --indent; }
//
    //__attribute__((no_instrument_function))
    //static Logger &get_instance()
    //{
    //    static Logger instance (get_file_name());
    //    return instance;
    //}
//
    //__attribute__((no_instrument_function))
    //static const char *get_file_name()
    //{
    //    return Logger::log_file_name;
    //}

    //__attribute__((no_instrument_function))
    //static void set_file_path (const char *path)
    //{
    //    if (get_instance().log_file_name == NULL)
    //        get_instance().log_file_name = path;
    //}


#endif