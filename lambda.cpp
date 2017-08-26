#include <stdlib.h>
#include <stdio.h>


template <class IN, class OUT>
class func{
    char type;
    union {
        OUT (*f)(IN);
        struct{
            func<IN,OUT>* orig;
            OUT (*mod)(IN, func<IN,OUT>*);
        };
    };

    public:
    OUT apply (IN);
    static void erase(func* f){
        if (f->type==1){
            erase(f->orig);
        }
        free(f);
    };
    static func* copy(func* f){
        func* newF = (func<IN, OUT>*) malloc(sizeof(func<IN, OUT>));
        if (f.type==0){
            newF->type=0;
            newF->f=f->f;
        } else {
            newF->type=1;
            newF->mod=f->mod;
            newF->orig=func::copy(f->orig);
        }
        return newF;
    }
    static func* apply(OUT (*mod)(IN, func*), func* f){
        func* newF = (func<IN, OUT>*) malloc(sizeof(func<IN, OUT>));
        newF -> type=1;
        newF -> orig=f;
        newF -> mod=mod;
        return newF;
    }
    static func* convert(OUT (*f)(IN)){
        func* newF = (func<IN, OUT>*) malloc(sizeof(func<IN, OUT>));
        newF -> type=0;
        newF -> f = f;
        return newF;
    }
};

template <class IN, class OUT>
OUT func<IN, OUT>::apply(IN i){
    if (type==0){
        return f(i);
    } else {
        return mod(i, orig);
    }
}


template <class IN, class OUT>
class lambda{
    func<IN,OUT>* pntr;

    OUT apply(IN i){
        return pntr->apply(i);
    };
    
};


int doubler(int i, func<int,int>* f){
    return 2*f->apply(2*i);
}


int a(int x){
    return x+1;
}



int main(){
    func<int,int>* da = func<int,int>::apply(doubler, func<int,int>::convert(a));
    for (int i =0; i<11; i++){
        printf("%i\t%i\n",i,da->apply(i));
    }
    func<int,int>::erase(da);
}
