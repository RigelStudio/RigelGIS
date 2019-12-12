#include "HttpRequest.h"
#include "Global.h"
#include <QFile>
#include <QTimer>
#include <QEventLoop>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QException>

QTimer* HttpRequest::m_pTimer = nullptr;
QNetworkAccessManager* HttpRequest::m_pNetManager = nullptr;

void HttpRequest::init()
{
	if (m_pNetManager == nullptr)
	{
		m_pNetManager = new QNetworkAccessManager;
	}
	if (m_pTimer == nullptr)
	{
		m_pTimer = new QTimer;
		m_pTimer->setInterval(1000000);//���ó�ʱʱ��Ϊ20s
		m_pTimer->setSingleShot(true);//���δ���
	}
}

QJsonObject HttpRequest::Request(QJsonObject input, RequestType methodtype, QString url)
{
	return QJsonObject();
}

QJsonObject HttpRequest::HttpGet(QString url)
{
	init();
	QString strToken = Core->UserToken;
	QNetworkRequest request;
	request.setUrl(QUrl(url));
	request.setRawHeader("Content-Type", "application/json");
	request.setRawHeader("Authorization", strToken.toLocal8Bit());
	request.setRawHeader("endpoint", "PC");
	QNetworkReply* reply = m_pNetManager->get(request);

	//timer�����жϳ�ʱ��EventLoop�����ȴ���Ӧ
	QEventLoop loop;
	connect(m_pTimer, &QTimer::timeout, &loop, &QEventLoop::quit);
	connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
	m_pTimer->start();
	loop.exec();

	if (m_pTimer->isActive())
	{
		m_pTimer->stop();
		QByteArray dataArray = reply->readAll();
		QString strDebug = QString::fromUtf8(dataArray);
		QJsonObject jsonData = QJsonDocument::fromJson(dataArray).object();
		int code = jsonData.value("code").toInt();
		if (code == 0)
		{
			return jsonData;
		}
		else
		{
			//�������
			QString strMsg = QString::number(code) + ": " + jsonData.value("message").toString();
			throw BIMException(strMsg);
		}
	}
	else
	{
		//���糬ʱ
		disconnect(m_pTimer, &QTimer::timeout, &loop, &QEventLoop::quit);
		disconnect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
		reply->abort();
		reply->deleteLater();
		throw BIMException(QStringLiteral("���糬ʱ��"));
	}
	return QJsonObject();
}

QJsonObject HttpRequest::HttpPost(QJsonObject input, QString url)
{
	init();

	QString strToken = Core->UserToken;
	QNetworkRequest request;
	request.setUrl(QUrl(url));
	request.setRawHeader("Content-Type", "application/json");
	request.setRawHeader("Authorization", strToken.toLocal8Bit());
	request.setRawHeader("endpoint", "PC");

	QJsonDocument inputDoc = QJsonDocument(input);
	QString str = QString(inputDoc.toJson());
	QNetworkReply* reply = m_pNetManager->post(request, inputDoc.toJson());

	//timer�����жϳ�ʱ��EventLoop�����ȴ���Ӧ
	QEventLoop loop;
	connect(m_pTimer, &QTimer::timeout, &loop, &QEventLoop::quit);
	connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
	m_pTimer->start();
	loop.exec();

	if (m_pTimer->isActive())
	{
		m_pTimer->stop();
		if (reply->error() != QNetworkReply::NoError)
		{
			//�������
			throw BIMException(reply->errorString());
		}
		else
		{
			QByteArray dataArray = reply->readAll();
			QJsonObject jsonData = QJsonDocument::fromJson(dataArray).object();
			return jsonData;
		}
	}
	else
	{
		//���糬ʱ
		disconnect(m_pTimer, &QTimer::timeout, &loop, &QEventLoop::quit);
		disconnect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
		reply->abort();
		reply->deleteLater();
		throw std::exception("Network Timeout!");
	}

	return QJsonObject();
}

QString HttpRequest::httpDownload(QString url, QString strFileDir)
{
	init();
	QString strToken = Core->UserToken;
	QNetworkRequest request;
	request.setUrl(QUrl(url));
	request.setRawHeader("Content-Type", "application/octet-stream");
	request.setRawHeader("Authorization", strToken.toLocal8Bit());
	request.setRawHeader("endpoint", "PC");
	QNetworkReply* reply = m_pNetManager->get(request);

	//timer�����жϳ�ʱ��EventLoop�����ȴ���Ӧ
	QEventLoop loop;
	connect(m_pTimer, &QTimer::timeout, &loop, &QEventLoop::quit);
	connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
	m_pTimer->start();
	loop.exec();

	if (m_pTimer->isActive())
	{
		m_pTimer->stop();
		
		QNetworkReply::NetworkError error = reply->error();
		QString strInfo = reply->rawHeader("Content-Disposition");
		if (error == QNetworkReply::NetworkError::NoError)
		{
			int index = strInfo.indexOf("filename=");
			QString fileName = strInfo.mid(index + 9); //����׺
			fileName = fileName.replace("\"", "");
			strFileDir += fileName;
			QFile file(strFileDir);

			if (file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Unbuffered))
			{
				QByteArray dataArray = reply->readAll();
				size_t len = file.write(dataArray, dataArray.size());
				QString strDebug = QString(dataArray);
				return strFileDir;
			}
			return "";
		}
		else
		{
			//�������
			//QString strMsg = QString::number(code) + ": " + jsonData.value("message").toString();
			//throw BIMException(strMsg);
		}
	}
	else
	{
		//���糬ʱ
		disconnect(m_pTimer, &QTimer::timeout, &loop, &QEventLoop::quit);
		disconnect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
		reply->abort();
		reply->deleteLater();
		throw BIMException(QStringLiteral("���糬ʱ��"));
	}
	return "";
}
