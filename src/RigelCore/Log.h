#ifndef LOG_H
#define LOG_H
#include "Export.h"
#include <fstream>
#include <sstream>
//#include <mutex>

enum LogLevel
{
	None	= 1,
	Info	= 1 << 1,
	Warning = 1 << 2,
	Error	= 1 << 3,
	AllLevel= Info | Warning | Error
};

enum LogMode
{
	Console = 1,
	LogFile = 1 << 1,
	AllMode = Console | LogFile
};

static std::ofstream s_logFile;
static int s_logLevel = AllLevel;
static LogMode s_logMode = AllMode;
//static std::mutex s_mutex;

class RIGELCORE_EXPORT LogMessage
{
public:
	LogMessage(char* file, int line, LogLevel level);
	~LogMessage();

	std::stringstream& logStream() { return *m_msgTemp; }

	void write();

private:
	//��log�ļ���д��
	void writeLogFile();

	void writeConsole();

private:
	LogLevel m_level;
	std::stringstream* m_msgTemp;
};

class RIGELCORE_EXPORT Loger
{
public:
	static void initLog(const std::string& logDir);

	//none ���ýض�ģʽ
	static void clearLog() {};

	//����log��ʾ��ʽ
	static void setOutMode(const LogMode mode);

	//����log�������
	static void setOutLevel(int level);

};

#define MSG_Error LogMessage( __FILE__, __LINE__, Error)
#define MSG_Warning LogMessage( __FILE__, __LINE__, Warning)
#define MSG_Info LogMessage( __FILE__, __LINE__, Info)

#define LOG(msg) MSG_## msg.logStream()

#define LOG_Error LOG(Error)
#define LOG_Warning LOG(Warning)
#define LOG_Info LOG(Info)

#endif//LOG_H