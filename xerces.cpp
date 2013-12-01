#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <memory>
#include <iostream>
#include <boost/optional.hpp>

// feels like a lost cause.

/*
svg datatypes

<boolean> bool
<Char> XMLChar
<Clock-value> std::chrono::duration
<color> struct colour {char r, g, b;};
<content-type> std::string
<coordinate> double
<focus>
<font-family-value>
<family-name>
<font-size-value>
<FuncIRI>
<ID>
<IDREF>
<integer>
<IRI>
<language-id>
<length> double
<list-of-content-types>
<list-of-family-names>
<list-of-language-ids>
<list-of-strings> std::vector<std::string>
<list-of-Ts>
<long> long
<NCName>
<number> double
<paint> struct
<path-data> bloody big struct
<points-data> std::vector<point>
<QName>
<string>
<transform> struct
<XML-Name>
<XML-NMTOKEN>
<XML-NMTOKENS>

*/

namespace svg
{

namespace attributes
{

struct viewBox
{
    float x = 0;
    float y = 0;
    float width = 0;
    float height = 0;
};

struct length
{
    float n;// = 0;
    enum 
    {
        ucs,
        in, 
        cm, 
        mm, 
        pt, 
        pc, 
        px,
        percent
    } unit;// = ucs;
};

struct preserveAspectRatio
{
    bool defer = false;
    enum 
    {
        none,
        xMinYMin,
        xMidYMin,
        xMaxYMin,
        xMinYMid,
        xMidYMid,
        xMaxYMid,
        xMinYMax,
        xMidYMax,
        xMaxYMax
    } align = xMidYMid;
    bool meet = false;
};

struct Clock_val
{
    float t;
    enum
    {
        s,
        ms
    } unit = s;
};

enum class focusable
{
    true_,
    false_,
    auto_
};

struct nav
{
    std::string next = "auto";
    std::string prev = "auto";
    std::string up = "auto";
    std::string up_right = "auto";
    std::string right = "auto";
    std::string down_right = "auto";
    std::string down = "auto";
    std::string down_left = "auto";
    std::string left = "auto";
    std::string up_left = "auto";
};

}

namespace element
{

struct desc
{
};
struct title
{
};
struct metadata
{
};
template<typename Allowed...>
struct switch_
{
    std::vector<boost::variant<Allowed..., switch_>> members;
};

struct g
{
    attribute::focusable focusable = attribute::focusable::auto_;
    attribute::nav nav;
};

typedef boost::variant<
                desc, title, metadata, switch_<desc, title, metadata>,
                animate, set, animateColor, animateTransform, animateMotion,
                animation,
                audio,
                discard,
                foreignObject,
                textArea,
                font, font_face,
                linearGradient, radialGradient,
                handler,
                image,
                prefetch,
                script,
                path, rect, circle, line, ellipse, polyline, polygon,
                solidColor,
                text,
                video,
                listener,
                g,
                defs,
                use,
                switch_<
                    desc, title, metadata, switch_<desc, title, metadata>,
                    animate, set, animateColor, animateTransform, animateMotion,
                    animation,
                    audio,
                    discard,
                    foreignObject,
                    textArea,
                    font, font_face,
                    linearGradient, radialGradient,
                    handler,
                    image,
                    prefetch,
                    script,
                    path, rect, circle, line, ellipse, polyline, polygon,
                    solidColor,
                    text,
                    video,
                    listener,
                    g,
                    defs,
                    use,
                    a
                >
                 > GCommon;

struct svg
{
    std::string version;
    enum profile
    {
        none,
        full,
        basic,
        tiny
    } baseProfile = none;
    
    length width = {100, length::percent};
    length height = {100, length::percent};
    boost::optional<viewBox> viewBox_;
    
    preserveAspectRatio preserdisableveAspectRatio_;
    boost::optional<Clock_val> snapshotTime;
    
    enum
    {
        forwardOnly,
        all
    } playbackOrder = all;
    
    enum
    {
        onLoad,
        onStart
    } timelineBegin = onLoad;
    
    std::string contentScriptType = "application/ecmascript";
    
    enum
    {
        magnify,
        disable
    } zoomAndPan = magnify;
    
    focusable focusable_ = focusable::auto_;
    nav nav_;
    
    std::vector<GCommon> children;
};

}

}

namespace
{
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
}

int main (int argc, char* args[]) {
using namespace xercesc;

    try {
        XMLPlatformUtils::Initialize();
    }
    catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        std::cout << "Error during initialization! :\n" << message << "\n";
        XMLString::release(&message);
        return 1;
    }

    auto errHandler = make_unique<HandlerBase>();
    auto parser = make_unique<XercesDOMParser>();
    parser->setErrorHandler(errHandler.get());
    parser->setValidationScheme(XercesDOMParser::Val_Always);
    parser->setDoNamespaces(true);


    auto xmlFile = "x1.svg";

    try {
        parser->parse(xmlFile);
    }
    catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        std::cout << "Exception message is: \n" << message << "\n";
        XMLString::release(&message);
        return -1;
    }
    catch (const DOMException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        std::cout << "Exception message is: \n" << message << "\n";
        XMLString::release(&message);
        return -1;
    }
    catch (const SAXParseException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        std::cout << "Exception message is: \n" << message << "\n";
        XMLString::release(&message);
        return -1;
    }
    catch (...) {
        std::cout << "Unexpected Exception \n" ;
        return -1;
    }

    return 0;
}
