
#pragma once

typedef std::string String;

struct VIdObj {
    String _vId = "";
    VIdObj ();
    VIdObj ( String s );
    VIdObj ( const char* s );

    String getVId();
    void setVId ( String s );
    void setVId ( const char* s );

    int getBk();
    String getBkStr();
    void setBk ( int n );

    int getChap();
    String getChapStr();
    void setChap ( int n );

    int getVer();
    String getVerStr();
    void setVer ( int n );

    String toString();

    ~VIdObj();
};
    
