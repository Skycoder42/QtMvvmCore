#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>

class Control : public QObject
{
	Q_OBJECT

	Q_PROPERTY(bool deleteOnClose READ deleteOnClose WRITE setDeleteOnClose NOTIFY deleteOnCloseChanged)

public:
	explicit Control(QObject *parent = nullptr);

	virtual void onShow();
	virtual void onClose();

	virtual Control *parentControl() const;

	bool deleteOnClose() const;

public slots:
	void show();
	void close();
	void setDeleteOnClose(bool deleteOnClose);

signals:
	void deleteOnCloseChanged(bool deleteOnClose);

private:
	bool _deleteOnClose;
};

Q_DECLARE_METATYPE(Control*)

#endif // CONTROL_H
