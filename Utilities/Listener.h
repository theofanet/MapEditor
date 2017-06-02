//
//  Listener.hpp
//  GameCube
//
//  Created by Theo Fanet on 17/07/16.
//  Copyright © 2016 Theo. All rights reserved.
//

#ifndef Listener_hpp
#define Listener_hpp

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <vector>
#include <functional>
#include <type_traits>
#include <utility>

using namespace std::placeholders;

template<class Sig>
class Signal;

#define signals public
#define slots /* nothing */

template<class... Args>
class Signal<void(Args...)>{
public:
    typedef std::function<void(Args...)> _Slot;
    
    void trigger(Args... args) const{
        typename std::vector<_Slot>::const_iterator i;
        _Slot t;
        int in = 1;
        for(i = _slots.begin(); i != _slots.end(); i++, in++){
            t = (*i);
            t( args... );
        }
    }
    
    void connect( _Slot slot ){
        _slots.push_back(slot);
    }
    
private:
    std::vector<_Slot> _slots;
};

#endif /* Listener_hpp */
