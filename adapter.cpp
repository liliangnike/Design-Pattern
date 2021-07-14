/*
    Adapter design pattern is an structural pattern. It make different incompatible objects to cooprate.

    One object -> Adapter -> Date Format/Interface can be supported by another object.

    For example, XML -> XML/JSON Adapter -> JSON analyzer.

    This demo example is basic implementation of design pattern according to adapter design pattern definitions and principles.
*/

#include <iostream>
#include <algorithm>

using namespace std;

// Defines interfaces used by client code
class client 
{
public:
    virtual ~client() = default;

    // client code does not JSON analyzer code, just only know that JSON format is needed
    virtual string xmlAnalysisRequest() const
    {
	return "I only can provide XML files.";
    }
};

// target object  - Json format file is needed
class target
{
public:
    string jsonAnalyzerRequest() const
    {
	// xml request might not understand this
	return "tupni eb dluohs elif nosJ";
    }
};

class adapter : public client
{
public:
    adapter(target *trgt) : _trgt(trgt) {}

    string xmlAnalysisRequest() const override
    {
	string str = _trgt->jsonAnalyzerRequest();
	reverse(str.begin(), str.end());
	return "After adpter, client XML can be analyzed. Client know what Json analyzer told is: " + str;
    }
private:
    target *_trgt;
};

void client_code(const client *clnt)
{
    cout << clnt->xmlAnalysisRequest();
};

int main()
{
    client *clt = new client;
    client_code(clt);
    cout << "\n";

    target *tgt = new target;
    cout << tgt->jsonAnalyzerRequest();
    cout << "\n";

    adapter *adpt = new adapter(tgt);
    client_code(adpt);
    cout << "\n";

    delete clt;
    delete tgt;
    delete adpt;

    return 0;
}
