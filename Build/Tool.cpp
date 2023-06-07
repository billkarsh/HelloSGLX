
#include "Tool.h"
#include "CGBL.h"
#include "Util.h"

#include "SglxCppClient.h"
using namespace std;


/* ---------------------------------------------------------------- */
/* Tool ----------------------------------------------------------- */
/* ---------------------------------------------------------------- */

Tool::Tool()
{
}


Tool::~Tool()
{
}


void Tool::entrypoint()
{
    if( GBL.cmd == "justConnect" )
        justConnect();
    else if( GBL.cmd == "enumDataDir" )
        enumDataDir();
    else if( GBL.cmd == "getDataDir" )
        getDataDir();
    else if( GBL.cmd == "getImecChanGains" )
        getImecChanGains();
    else if( GBL.cmd == "getParams" )
        getParams();
    else if( GBL.cmd == "getParamsImecCommon" )
        getParamsImecCommon();
    else if( GBL.cmd == "getParamsImecProbe" )
        getParamsImecProbe();
    else if( GBL.cmd == "getParamsOneBox" )
        getParamsOneBox();
    else if( GBL.cmd == "getProbeList" )
        getProbeList();
    else if( GBL.cmd == "getRunName" )
        getRunName();
    else if( GBL.cmd == "getStreamAcqChans" )
        getStreamAcqChans();
    else if( GBL.cmd == "getStreamI16ToVolts" )
        getStreamI16ToVolts();
    else if( GBL.cmd == "getStreamMaxInt" )
        getStreamMaxInt();
    else if( GBL.cmd == "getStreamNP" )
        getStreamNP();
    else if( GBL.cmd == "getStreamSampleRate" )
        getStreamSampleRate();
    else if( GBL.cmd == "getStreamSaveChans" )
        getStreamSaveChans();
    else if( GBL.cmd == "getStreamSN" )
        getStreamSN();
    else if( GBL.cmd == "getStreamVoltageRange" )
        getStreamVoltageRange();
    else if( GBL.cmd == "getTime" )
        getTime();
    else if( GBL.cmd == "getVersion" )
        getVersion();
    else if( GBL.cmd == "isInitialized" )
        isInitialized();
    else if( GBL.cmd == "isRunning" )
        isRunning();
    else if( GBL.cmd == "isSaving" )
        isSaving();
    else if( GBL.cmd == "isUserOrder" )
        isUserOrder();
    else if( GBL.cmd == "opto_emit" )
        opto_emit();
    else if( GBL.cmd == "opto_getAttenuations" )
        opto_getAttenuations();
    else if( GBL.cmd == "setAnatomy_Pinpoint" )
        setAnatomy_Pinpoint();
    else if( GBL.cmd == "setAudioEnable" )
        setAudioEnable();
    else if( GBL.cmd == "setAudioParams" )
        setAudioParams();
    else if( GBL.cmd == "setDataDir" )
        setDataDir();
    else if( GBL.cmd == "setDigitalOut" )
        setDigitalOut();
    else if( GBL.cmd == "setMetadata" )
        setMetadata();
    else if( GBL.cmd == "setMultiDriveEnable" )
        setMultiDriveEnable();
    else if( GBL.cmd == "setNextFileName" )
        setNextFileName();
    else if( GBL.cmd == "setParams" )
        setParams();
    else if( GBL.cmd == "setParamsImecCommon" )
        setParamsImecCommon();
    else if( GBL.cmd == "setParamsImecProbe" )
        setParamsImecProbe();
    else if( GBL.cmd == "setParamsOneBox" )
        setParamsOneBox();
    else if( GBL.cmd == "setRecordingEnable" )
        setRecordingEnable();
    else if( GBL.cmd == "setRunName" )
        setRunName();
    else if( GBL.cmd == "setTriggerOffBeep" )
        setTriggerOffBeep();
    else if( GBL.cmd == "setTriggerOnBeep" )
        setTriggerOnBeep();
    else if( GBL.cmd == "startRun" )
        startRun();
    else if( GBL.cmd == "stopRun" )
        stopRun();
    else if( GBL.cmd == "triggerGT" )
        triggerGT();
    else
        Log() << QString("error: Unknown command [%1].").arg( GBL.cmd );
}


void Tool::justConnect()
{
    printf( "\nCalling connect...\n\n" );

    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {
        printf( "vers %s\n", S.vers.c_str() );
        printf( "host %s\n", S.host.c_str() );
        printf( "port %d\n", S.port );
        sglx_close( S );
    }
    else
        printf( "error [%s]\n", S.err.c_str() );
}


void Tool::enumDataDir()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        vector<string>  vstr;

        if( sglx_enumDataDir( vstr, S, GBL.args.toInt() ) ) {
            for( int i = 0, n = vstr.size(); i < n; ++i )
                Log() << vstr[i].c_str();
        }
        else
            goto error;

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::getDataDir()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        string str;

        if( sglx_getDataDir( str, S, GBL.args.toInt() ) )
            Log() << str.c_str();
        else
            goto error;

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::getImecChanGains()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        const QStringList   sl = GBL.args.split(
                                    QRegExp("\\s+"),
                                    QString::SkipEmptyParts );

        if( sl.size() != 2 ) {
            Log() << "error: getImecChanGains requires {ip, chan} parameters.";
            return;
        }

        double  ap, lf;

        if( sglx_getImecChanGains( ap, lf, S, sl[0].toInt(), sl[1].toInt() ) ) {
            Log() << ap;
            Log() << lf;
        }
        else
            goto error;

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::getParams()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        map<string,string>   mstrstr;

        if( sglx_getParams( mstrstr, S ) ) {

            map<string,string>::iterator
                it  = mstrstr.begin(),
                end = mstrstr.end();

            while( it != end ) {
                Log() << QString("%1=%2")
                    .arg( it->first.c_str() )
                    .arg( it->second.c_str() );
                ++it;
            }
        }
        else
            goto error;

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::getParamsImecCommon()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        map<string,string>   mstrstr;

        if( sglx_getParamsImecCommon( mstrstr, S ) ) {

            map<string,string>::iterator
                it  = mstrstr.begin(),
                end = mstrstr.end();

            while( it != end ) {
                Log() << QString("%1=%2")
                    .arg( it->first.c_str() )
                    .arg( it->second.c_str() );
                ++it;
            }
        }
        else
            goto error;

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::getParamsImecProbe()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        map<string,string>   mstrstr;

        if( sglx_getParamsImecProbe( mstrstr, S, GBL.args.toInt() ) ) {

            map<string,string>::iterator
                it  = mstrstr.begin(),
                end = mstrstr.end();

            while( it != end ) {
                Log() << QString("%1=%2")
                    .arg( it->first.c_str() )
                    .arg( it->second.c_str() );
                ++it;
            }
        }
        else
            goto error;

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::getParamsOneBox()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        map<string,string>   mstrstr;

        if( sglx_getParamsOneBox( mstrstr, S, GBL.args.toInt() ) ) {

            map<string,string>::iterator
                it  = mstrstr.begin(),
                end = mstrstr.end();

            while( it != end ) {
                Log() << QString("%1=%2")
                    .arg( it->first.c_str() )
                    .arg( it->second.c_str() );
                ++it;
            }
        }
        else
            goto error;

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::getProbeList()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        string str;

        if( sglx_getProbeList( str, S ) )
            Log() << str.c_str();
        else
            goto error;

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::getRunName()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        string str;

        if( sglx_getRunName( str, S ) )
            Log() << str.c_str();
        else
            goto error;

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::getStreamAcqChans()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        const QStringList   sl = GBL.args.split(
                                    QRegExp("\\s+"),
                                    QString::SkipEmptyParts );

        if( sl.size() != 2 ) {
            Log() << "error: getStreamAcqChans requires {js, ip} parameters.";
            return;
        }

        vector<int> vi32;

        if( sglx_getStreamAcqChans( vi32, S, sl[0].toInt(), sl[1].toInt() ) ) {
            for( int i = 0, n = vi32.size(); i < n; ++i )
                Log() << QString("%1").arg( vi32[i] );
        }
        else
            goto error;

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::getStreamI16ToVolts()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        const QStringList   sl = GBL.args.split(
                                    QRegExp("\\s+"),
                                    QString::SkipEmptyParts );

        if( sl.size() != 3 ) {
            Log() << "error: getStreamI16ToVolts requires {js, ip, chan} parameters.";
            return;
        }

        double  mult;

        if( sglx_getStreamI16ToVolts( mult, S, sl[0].toInt(), sl[1].toInt(), sl[2].toInt() ) ) {
            Log() << mult;
        }
        else
            goto error;

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::getStreamMaxInt()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        const QStringList   sl = GBL.args.split(
                                    QRegExp("\\s+"),
                                    QString::SkipEmptyParts );

        if( sl.size() != 2 ) {
            Log() << "error: getStreamMaxInt requires {js, ip} parameters.";
            return;
        }

        int maxi;

        if( sglx_getStreamMaxInt( maxi, S, sl[0].toInt(), sl[1].toInt() ) )
            Log() << maxi;
        else
            goto error;

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::getStreamNP()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        int np;

        if( sglx_getStreamNP( np, S, GBL.args.toInt() ) )
            Log() << np;
        else
            goto error;

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::getStreamSampleRate()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        const QStringList   sl = GBL.args.split(
                                    QRegExp("\\s+"),
                                    QString::SkipEmptyParts );

        if( sl.size() != 2 ) {
            Log() << "error: getStreamSampleRate requires {js, ip} parameters.";
            return;
        }

        Log() <<
        sglx_getStreamSampleRate( S, sl[0].toInt(), sl[1].toInt() );

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::getStreamSaveChans()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        const QStringList   sl = GBL.args.split(
                                    QRegExp("\\s+"),
                                    QString::SkipEmptyParts );

        if( sl.size() != 2 ) {
            Log() << "error: getStreamSaveChans requires {js, ip} parameters.";
            return;
        }

        vector<int> vi32;

        if( sglx_getStreamSaveChans( vi32, S, sl[0].toInt(), sl[1].toInt() ) ) {
            for( int i = 0, n = vi32.size(); i < n; ++i )
                Log() << QString("%1").arg( vi32[i] );
        }
        else
            goto error;

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::getStreamSN()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        const QStringList   sl = GBL.args.split(
                                    QRegExp("\\s+"),
                                    QString::SkipEmptyParts );

        if( sl.size() != 2 ) {
            Log() << "error: getStreamSN requires {js, ip} parameters.";
            return;
        }

        string  sn;
        int     slot;

        if( sglx_getStreamSN( slot, sn, S, sl[0].toInt(), sl[1].toInt() ) ) {
            Log() << slot;
            Log() << sn.c_str();
        }
        else
            goto error;

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::getStreamVoltageRange()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        const QStringList   sl = GBL.args.split(
                                    QRegExp("\\s+"),
                                    QString::SkipEmptyParts );

        if( sl.size() != 2 ) {
            Log() << "error: getStreamVoltageRange requires {js, ip} parameters.";
            return;
        }

        double  lo, hi;

        if( sglx_getStreamVoltageRange( lo, hi, S, sl[0].toInt(), sl[1].toInt() ) ) {
            Log() << lo;
            Log() << hi;
        }
        else
            goto error;

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::getTime()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        Log() << sglx_getTime( S );

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::getVersion()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        string  s;

        if( sglx_getVersion( s, S ) )
            Log() << s.c_str();
        else
            goto error;

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::isInitialized()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        bool    ready;

        if( sglx_isInitialized( ready, S ) )
            Log() << ready;
        else
            goto error;

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::isRunning()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        bool    running;

        if( sglx_isRunning( running, S ) )
            Log() << running;
        else
            goto error;

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::isSaving()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        bool    saving;

        if( sglx_isSaving( saving, S ) )
            Log() << saving;
        else
            goto error;

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::isUserOrder()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        const QStringList   sl = GBL.args.split(
                                    QRegExp("\\s+"),
                                    QString::SkipEmptyParts );

        if( sl.size() != 2 ) {
            Log() << "error: isUserOrder requires {js, ip} parameters.";
            return;
        }

        bool    usr;

        if( sglx_isUserOrder( usr, S, sl[0].toInt(), sl[1].toInt() ) ) {
            Log() << usr;
        }
        else
            goto error;

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::opto_emit()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        const QStringList   sl = GBL.args.split(
                                    QRegExp("\\s+"),
                                    QString::SkipEmptyParts );

        if( sl.size() != 3 ) {
            Log() << "error: opto_emit requires {ip, color, site} parameters.";
            return;
        }

        if( !sglx_opto_emit( S, sl[0].toInt(), sl[1].toInt(), sl[2].toInt() ) )
            goto error;

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::opto_getAttenuations()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        const QStringList   sl = GBL.args.split(
                                    QRegExp("\\s+"),
                                    QString::SkipEmptyParts );

        if( sl.size() != 2 ) {
            Log() << "error: opto_getAttenuations requires {ip, color} parameters.";
            return;
        }

        vector<double>  vdbl;

        if( sglx_opto_getAttenuations( vdbl, S, sl[0].toInt(), sl[1].toInt() ) ) {
            for( int i = 0, n = vdbl.size(); i < n; ++i )
                Log() << vdbl[i];
        }
        else
            goto error;

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::setAnatomy_Pinpoint()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        if( !sglx_setAnatomy_Pinpoint( S, GBL.args.toStdString() ) )
            goto error;

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::setAudioEnable()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        if( !sglx_setAudioEnable( S, GBL.args.toInt() ) )
            goto error;

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::setAudioParams()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        const QStringList   sl = GBL.args.split(
                                    QRegExp("\\s+"),
                                    QString::SkipEmptyParts );

        map<string,string>  mstrstr;

        for( int i = 1, n = sl.size(); i < n; ++i ) {
            const string    &s = sl[i].toStdString();
            int             eq = s.find( '=' );
            mstrstr[s.substr( 0, eq )] = s.substr( eq + 1 );
        }

        if( !sglx_setAudioParams( S, sl[0].toStdString(), mstrstr ) )
            goto error;

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::setDataDir()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        const QStringList   sl = GBL.args.split(
                                    QRegExp("\\s+"),
                                    QString::SkipEmptyParts );

        if( !sglx_setDataDir( S, sl[0].toInt(), sl[1].toStdString() ) )
            goto error;

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::setDigitalOut()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        const QStringList   sl = GBL.args.split(
                                    QRegExp("\\s+"),
                                    QString::SkipEmptyParts );

        if( !sglx_setDigitalOut( S, sl[0].toInt(), sl[1].toStdString() ) )
            goto error;

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::setMetadata()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        const QStringList   sl = GBL.args.split(
                                    QRegExp("\\s+"),
                                    QString::SkipEmptyParts );

        map<string,string>  mstrstr;

        for( int i = 0, n = sl.size(); i < n; ++i ) {
            const string    &s = sl[i].toStdString();
            int             eq = s.find( '=' );
            mstrstr[s.substr( 0, eq )] = s.substr( eq + 1 );
        }

        if( !sglx_setMetadata( S, mstrstr ) )
            goto error;

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::setMultiDriveEnable()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        if( !sglx_setMultiDriveEnable( S, GBL.args.toInt() ) )
            goto error;

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::setNextFileName()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        if( !sglx_setNextFileName( S, GBL.args.toStdString() ) )
            goto error;

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::setParams()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        const QStringList   sl = GBL.args.split(
                                    QRegExp("\\s+"),
                                    QString::SkipEmptyParts );

        map<string,string>  mstrstr;

        for( int i = 0, n = sl.size(); i < n; ++i ) {
            const string    &s = sl[i].toStdString();
            int             eq = s.find( '=' );
            mstrstr[s.substr( 0, eq )] = s.substr( eq + 1 );
        }

        if( !sglx_setParams( S, mstrstr ) )
            goto error;

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::setParamsImecCommon()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        const QStringList   sl = GBL.args.split(
                                    QRegExp("\\s+"),
                                    QString::SkipEmptyParts );

        map<string,string>  mstrstr;

        for( int i = 0, n = sl.size(); i < n; ++i ) {
            const string    &s = sl[i].toStdString();
            int             eq = s.find( '=' );
            mstrstr[s.substr( 0, eq )] = s.substr( eq + 1 );
        }

        if( !sglx_setParamsImecCommon( S, mstrstr ) )
            goto error;

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::setParamsImecProbe()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        const QStringList   sl = GBL.args.split(
                                    QRegExp("\\s+"),
                                    QString::SkipEmptyParts );

        map<string,string>  mstrstr;

        for( int i = 1, n = sl.size(); i < n; ++i ) {
            const string    &s = sl[i].toStdString();
            int             eq = s.find( '=' );
            mstrstr[s.substr( 0, eq )] = s.substr( eq + 1 );
        }

        if( !sglx_setParamsImecProbe( S, mstrstr, sl[0].toInt() ) )
            goto error;

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::setParamsOneBox()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        const QStringList   sl = GBL.args.split(
                                    QRegExp("\\s+"),
                                    QString::SkipEmptyParts );

        map<string,string>  mstrstr;

        for( int i = 1, n = sl.size(); i < n; ++i ) {
            const string    &s = sl[i].toStdString();
            int             eq = s.find( '=' );
            mstrstr[s.substr( 0, eq )] = s.substr( eq + 1 );
        }

        if( !sglx_setParamsOneBox( S, mstrstr, sl[0].toInt() ) )
            goto error;

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::setRecordingEnable()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        if( !sglx_setRecordingEnable( S, GBL.args.toInt() ) )
            goto error;

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::setRunName()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        if( !sglx_setRunName( S, GBL.args.toStdString() ) )
            goto error;

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::setTriggerOffBeep()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        const QStringList   sl = GBL.args.split(
                                    QRegExp("\\s+"),
                                    QString::SkipEmptyParts );

        if( !sglx_setTriggerOffBeep( S, sl[0].toInt(), sl[1].toInt() ) )
            goto error;

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::setTriggerOnBeep()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        const QStringList   sl = GBL.args.split(
                                    QRegExp("\\s+"),
                                    QString::SkipEmptyParts );

        if( !sglx_setTriggerOnBeep( S, sl[0].toInt(), sl[1].toInt() ) )
            goto error;

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::startRun()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        string  run;

        if( !GBL.args.isEmpty() )
            run = GBL.args.toStdString();

        if( !sglx_startRun( S, run ) )
            goto error;

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::stopRun()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        if( !sglx_stopRun( S ) )
            goto error;

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


void Tool::triggerGT()
{
    t_sglxconn  S;

    if( sglx_connect_std( S, GBL.host ) ) {

        const QStringList   sl = GBL.args.split(
                                    QRegExp("\\s+"),
                                    QString::SkipEmptyParts );

        if( !sglx_triggerGT( S, sl[0].toInt(), sl[1].toInt() ) )
            goto error;

        sglx_close( S );
    }
    else {
error:
        printf( "error [%s]\n", S.err.c_str() );
    }
}


