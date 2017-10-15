#ifndef QTMVVMBINDING_H
#define QTMVVMBINDING_H

#include <QObject>
#include <QMetaProperty>
#include <QtGlobal>

class QtMvvmBinding : public QObject
{
	Q_OBJECT

public:
	enum BindingDirectionFlag {
		SingleInit = 0x01,
		OneWayFromControl = (0x02 | SingleInit),
		OneWayToControl = 0x04,
		TwoWay = (OneWayFromControl | OneWayToControl)
	};
	Q_DECLARE_FLAGS(BindingDirection, BindingDirectionFlag)
	Q_FLAG(BindingDirection)

	static QtMvvmBinding *bind(QObject *control, const char *controlProperty, QObject *view, const char *viewProperty, BindingDirection type = TwoWay);
	static QtMvvmBinding *bind(QObject *control, const QMetaProperty &controlProperty, QObject *view, const QMetaProperty &viewProperty, BindingDirection type = TwoWay);

private slots:
	void controlTrigger();
	void viewTrigger();

private:
	QtMvvmBinding(QObject *control, const QMetaProperty &controlProperty, QObject *view, const QMetaProperty &viewProperty);

	void init();
	void bindFrom();
	void bindTo();

	QObject *_control;
	QObject *_view;
	QMetaProperty _controlProperty;
	QMetaProperty _viewProperty;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QtMvvmBinding::BindingDirection)

#endif // QTMVVMBINDING_H
