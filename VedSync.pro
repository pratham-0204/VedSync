QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    active_appointment.cpp \
    dashboard_doctor.cpp \
    dashboard_patient.cpp \
    doctorinfoandappointment.cpp \
    doctorsignup.cpp \
    main.cpp \
    mainwindow.cpp \
    patientsignup.cpp \
    signin.cpp \
    signup.cpp \
    usersignin.cpp

HEADERS += \
    DEFINITIONS.h \
    active_appointment.h \
    dashboard_doctor.h \
    dashboard_patient.h \
    doctorinfoandappointment.h \
    doctorsignup.h \
    mainwindow.h \
    patientsignup.h \
    signin.h \
    signup.h \
    usersignin.h

FORMS += \
    active_appointment.ui \
    dashboard_doctor.ui \
    dashboard_patient.ui \
    doctorinfoandappointment.ui \
    doctorsignup.ui \
    mainwindow.ui \
    patientsignup.ui \
    signin.ui \
    signup.ui \
    usersignin.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    VedSync.db
