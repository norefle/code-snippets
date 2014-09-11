#include "modules/bind.hpp"

#include <memory>
#include <iostream>

namespace module
{

template<typename TResult, typename TArgument>
class TBaseFunctor
{
public:
    virtual TResult operator ()(TArgument argument) = 0;
    virtual ~TBaseFunctor() { }
};

template<typename TResult, typename TObject, typename TArgument>
class TMemberFunctor : public TBaseFunctor<TResult, TArgument>
{
public:
    typedef TResult (TObject::* TMethod)(TArgument);
    TMemberFunctor(TObject* object, TMethod method)
        : object_(object)
        , method_(method)
    {
    }

    virtual TResult operator ()(TArgument argument)
    {
        return (object_->*method_)(argument);
    }

private:
    TObject *object_;
    TMethod method_;
};

template<typename TResult, typename TArgument>
class Functor
{
public:
    typedef TBaseFunctor<TResult, TArgument> TImplementation;
    typedef std::shared_ptr<TImplementation> TImplementationPtr;

    Functor(const TImplementationPtr& implementation, TArgument argument)
        : implementation_(implementation)
        , argument_(argument)
    {
    }

    TResult operator ()()
    {
        return (*implementation_)(argument_);
    }

private:
    TImplementationPtr implementation_;
    TArgument argument_;
};

template<typename TResult, typename TObject, typename TArgument>
Functor<TResult, TArgument> bind
(
    TObject* object,
    TResult (TObject::* method)(TArgument),
    TArgument argument
)
{
    typedef Functor<TResult, TArgument> TExactFunctor;
    return TExactFunctor(typename TExactFunctor::TImplementationPtr(new TMemberFunctor<TResult, TObject, TArgument>(object, method)), argument);
}

namespace
{

class Bindable
{
public:
    Bindable(bool publicValue, double privateValue)
        : publicValue_(publicValue)
        , privateValue_(privateValue)
    {
    }

    bool setPublic(bool newValue)
    {
        const bool oldValue = publicValue_;
        publicValue_ = newValue;
        return oldValue;
    }

    bool getPupblic() const { return publicValue_; }
    double getPrivate() const { return privateValue_; }

    Functor<void, double> getFunctor(double value)
    {
        return bind(this, &Bindable::setPrivate, value);
    }

private:
    void setPrivate(double newValue)
    {
        privateValue_ = newValue;
    }

private:
    bool publicValue_;
    double privateValue_;
};

}

bool BinderModule::execute(const lib::ArgumentCollection& /*commandLine*/)
{
    Bindable bindable(false, 0.0);

    std::cout << "Before: { " << bindable.getPupblic() << " , " << bindable.getPrivate() << "}" << std::endl;

    auto onPrivate = bindable.getFunctor(100.0);
    auto onPublic = bind(&bindable, &Bindable::setPublic, true);

    onPrivate();
    onPublic();

    std::cout << "After: { " << bindable.getPupblic() << " , " << bindable.getPrivate() << "}" << std::endl;

    return true;
}

} // module
