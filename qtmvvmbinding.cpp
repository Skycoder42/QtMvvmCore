#include "qtmvvmbinding.h"
#include <QDebug>

QtMvvmBinding::QtMvvmBinding(QObject *control, const QMetaProperty &controlProperty, QObject *view, const QMetaProperty &viewProperty) :
	QObject(view),
	_control(control),
	_view(view),
	_controlProperty(controlProperty),
	_viewProperty(viewProperty)
{
	connect(_control, &QObject::destroyed,
			this, &QtMvvmBinding::deleteLater);
}

QtMvvmBinding *QtMvvmBinding::bind(QObject *control, const char *controlProperty, QObject *view, const char *viewProperty, BindingDirection type)
{
	if(!control) {
		qWarning() << "Control must not be (null)";
		return nullptr;
	}
	auto mC = control->metaObject();
	auto piC = mC->indexOfProperty(controlProperty);
	if(piC == -1) {
		qWarning() << "Control of type" << mC->className() << "has no property named" << controlProperty;
		return nullptr;
	}

	if(!view) {
		qWarning() << "View must not be (null)";
		return nullptr;
	}
	auto mW = view->metaObject();
	auto piW = mW->indexOfProperty(viewProperty);
	if(piW == -1) {
		qWarning() << "Control of type" << mW->className() << "has no property named" << viewProperty;
		return nullptr;
	}

	return bind(control, mC->property(piC), view, mW->property(piW), type);
}

QtMvvmBinding *QtMvvmBinding::bind(QObject *control, const QMetaProperty &controlProperty, QObject *view, const QMetaProperty &viewProperty, BindingDirection type)
{
	//check not null
	if(!control) {
		qWarning() << "Control must not be (null)";
		return nullptr;
	}
	if(!view) {
		qWarning() << "View must not be (null)";
		return nullptr;
	}

	auto binder = new QtMvvmBinding(control, controlProperty, view, viewProperty);

	if(type.testFlag(SingleInit)) {
		if(!controlProperty.isReadable()) {
			qWarning() << "Control property" << controlProperty.name()
					   << "of" << controlProperty.enclosingMetaObject()->className()
					   << "is not readable";
		}
		if(!viewProperty.isWritable()) {
			qWarning() << "View property" << viewProperty.name()
					   << "of" << viewProperty.enclosingMetaObject()->className()
					   << "is not writable";
		}
		binder->init();
	}

	if(type.testFlag(OneWayFromControl)) {
		if(!controlProperty.hasNotifySignal()) {
			qWarning() << "Control property" << controlProperty.name()
					   << "of" << controlProperty.enclosingMetaObject()->className()
					   << "has no notify singal";
		}
		binder->bindFrom();
	}

	if(type.testFlag(OneWayToControl)) {
		if(!viewProperty.isReadable()) {
			qWarning() << "View property" << viewProperty.name()
					   << "of" << viewProperty.enclosingMetaObject()->className()
					   << "is not readable";
		}
		if(!controlProperty.isWritable()) {
			qWarning() << "Control property" << controlProperty.name()
					   << "of" << controlProperty.enclosingMetaObject()->className()
					   << "is not writable";
		}
		if(!viewProperty.hasNotifySignal()) {
			qWarning() << "View property" << viewProperty.name()
					   << "of" << viewProperty.enclosingMetaObject()->className()
					   << "has no notify singal";
		}
		binder->bindTo();
	}

	return binder;
}

void QtMvvmBinding::controlTrigger()
{
	_viewProperty.write(_view, _controlProperty.read(_control));
}

void QtMvvmBinding::viewTrigger()
{
	_controlProperty.write(_control, _viewProperty.read(_view));
}

void QtMvvmBinding::init()
{
	_viewProperty.write(_view, _controlProperty.read(_control));
}

void QtMvvmBinding::bindFrom()
{
	auto signal = _controlProperty.notifySignal();
	auto trigger = metaObject()->method(metaObject()->indexOfSlot("controlTrigger()"));
	connect(_control, signal, this, trigger);
}

void QtMvvmBinding::bindTo()
{
	auto signal = _viewProperty.notifySignal();
	auto trigger = metaObject()->method(metaObject()->indexOfSlot("viewTrigger()"));
	connect(_view, signal, this, trigger);
}
