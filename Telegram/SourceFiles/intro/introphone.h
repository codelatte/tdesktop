/*
This file is part of Telegram Desktop,
an unofficial desktop messaging app, see https://telegram.org

Telegram Desktop is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

It is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

Full license: https://github.com/telegramdesktop/tdesktop/blob/master/LICENSE
Copyright (c) 2014 John Preston, https://tdesktop.com
*/
#pragma once

#include <QtWidgets/QWidget>
#include "gui/flatbutton.h"
#include "gui/phoneinput.h"
#include "gui/countrycodeinput.h"
#include "gui/countryinput.h"
#include "intro.h"

class IntroPhone : public IntroStage, public Animated, public RPCSender {
	Q_OBJECT

public:

	IntroPhone(IntroWidget *parent);

	void paintEvent(QPaintEvent *e);
	void resizeEvent(QResizeEvent *e);

	bool animStep(float64 ms);

	void selectCountry(const QString &country);

	void activate();
	void deactivate();
	void onNext();
	void onBack();

	void phoneCheckDone(const MTPauth_CheckedPhone &result);
	void phoneSubmitDone(const MTPauth_SentCode &result);
	bool phoneSubmitFail(const RPCError &error);

	void toSignUp();

public slots:

	void countryChanged();
	void onSelectClose();
	void onInputChange();
	void onSubmitPhone(bool force = false);
	void onCheckRequest();

private:

	QString fullNumber() const;
	void disableAll();
	void enableAll(bool failed);
	void stopCheck();

	void showError(const QString &err, bool signUp = false);

	QString error;
	anim::fvalue errorAlpha;

	bool changed;
	FlatButton next;

	QRect textRect;

	CountryInput country;
	PhoneInput phone;
	CountryCodeInput code;

	FlatLabel _signup;
	QPixmap _signupCache;
	bool _showSignup;

	QString sentPhone;
	mtpRequestId sentRequest;

	QTimer checkRequest;
};
