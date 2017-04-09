#ifndef COREMESSAGE_H
#define COREMESSAGE_H

#include "messageresult.h"
#include "coreapp.h"
#include <QUrl>
#include <functional>

namespace CoreMessage
{

MessageResult *message(const CoreApp::MessageConfig &config);

MessageResult *information(const QString &title,
						   const QString &text,
						   const QString &okText = {});
bool information(const QString &title,
				 const QString &text,
				 std::function<void()> onResult,
				 const QString &okText = {});

MessageResult *question(const QString &title,
						const QString &text,
						const QString &yesText = {},
						const QString &noText = {});
bool question(const QString &title,
			  const QString &text,
			  std::function<void(bool)> onResult,
			  const QString &yesText = {},
			  const QString &noText = {});

MessageResult *warning(const QString &title,
					   const QString &text,
					   const QString &okText = {});
bool warning(const QString &title,
			 const QString &text,
			 std::function<void()> onResult,
			 const QString &okText = {});

MessageResult *critical(const QString &title,
						const QString &text,
						const QString &okText = {});
bool critical(const QString &title,
			  const QString &text,
			  std::function<void()> onResult,
			  const QString &okText = {});

bool about(const QString &content,
		   bool includeCompany = true,
		   const QUrl &companyUrl = QUrl(),
		   bool includeQtVersion = true);

MessageResult *getInput(const QString &title,
						const QString &text,
						const char *inputType,
						const QVariant &defaultValue = {},
						const QVariantMap &editProperties = {},
						const QString &okText = {},
						const QString &cancelText = {});
MessageResult *getInput(const QString &title,
						const QString &text,
						int inputType,
						const QVariant &defaultValue = {},
						const QVariantMap &editProperties = {},
						const QString &okText = {},
						const QString &cancelText = {});
bool getInput(const QString &title,
			  const QString &text,
			  const char *inputType,
			  std::function<void(QVariant)> onResult,
			  const QVariant &defaultValue = {},
			  const QVariantMap &editProperties = {},
			  const QString &okText = {},
			  const QString &cancelText = {});
bool getInput(const QString &title,
			  const QString &text,
			  int inputType,
			  std::function<void(QVariant)> onResult,
			  const QVariant &defaultValue = {},
			  const QVariantMap &editProperties = {},
			  const QString &okText = {},
			  const QString &cancelText = {});

}

#endif // COREMESSAGE_H
