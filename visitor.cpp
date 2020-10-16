/*
 * visitor.cpp
 * Copyright (C) 2020 dmytro <dmytro@LWO1-LHP-A05509>
 *
 * Distributed under terms of the MIT license.
 */

#include <iostream>
using namespace std;

// #include "visitor.h"

#include <vector>
template <typename T>
using vec = std::vector<T>;

#include <memory>
template <typename T>
using uptr = std::unique_ptr<T>;

class ivis;
struct iob{
    virtual void show()const = 0;
    //virtual void accept(uptr<ivis>) = 0;
    virtual void accept(const uptr<ivis>&) = 0;
    static char c;
};
char iob::c = 'i';

class oba;
class obb;

struct ivis{
    virtual void vis(const oba*)=0;
    virtual void vis( const obb*)=0;
};

class oba : public iob {
    public:
    virtual void accept(const uptr<ivis>& v) override {v->vis(this);}
    void show()const override {
        cout << iob::c  << 'a' <<endl;
    }
};

class obb : public iob {
    public:
    virtual void accept(const uptr<ivis>& v) override {v->vis(this);}
    void show()const override {
        cout << iob::c  << 'b' <<endl;
    }
};

class visa : public ivis {
    /*
    void vis(const oba& ob)override { ob.show(); }
    void vis(const obb& ob)override { ob.show(); }
    */

    void vis( const oba* ob)override { cout << "visa logic"<<endl; ob->show(); }
    void vis( const obb* ob)override { cout << "visa logic"<<endl; ob->show(); }
};

class visb : public ivis {
    void vis( const oba* ob)override { cout << "visb logic"<<endl; ob->show(); }
    void vis( const obb* ob)override { cout << "visb logic"<<endl; ob->show(); }
};

void a(  ){
    vec< uptr<iob> > obs;
    obs.push_back( std::make_unique<oba>());
    obs.push_back( std::make_unique<obb>());

    uptr<ivis> v = std::make_unique<visb>();
    for (auto& e:obs){
        e->accept(v);
    }

    v = std::make_unique<visa>();
    for (auto& e:obs){
        e->accept(v);
    }
}

void b(){
    /*
    vec< iob* >  v = {new oba, new obb};

    visb vb;
    for (auto& e:v){
        vb.vis(*e);
    }
    */
}

int main(){
    oba a;
//    obb b;
    uptr<iob> pa = std::make_unique<oba>();
    //  uptr<iob> pb = std::make_unique<obb>();
    //vec< uptr<iob> > v {std::make_unique<oba>(), std::make_unique<obb>()};
    //vec< uptr<iob> > v {std::move( std::make_unique<oba>() )};
    // vec< uptr<iob> > v {std::move( pa )};
    vec< uptr<iob> > v;
    v.push_back( {std::move( pa )});
    ::a();

}
