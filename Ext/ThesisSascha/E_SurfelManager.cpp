#ifdef MINSG_EXT_THESISSASCHA

#include "E_SurfelManager.h"
#include "E_Preprocessor.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

#include <Util/StringIdentifier.h>
#include <Util/GenericAttribute.h>
#include <Util/IO/FileName.h>
#include <Util/StringUtils.h>

#include <E_Util/E_Utils.h>
#include <E_MinSG/Core/Nodes/E_Node.h>

namespace E_MinSG{
namespace ThesisSascha{
using namespace Util;
using namespace E_Util;

typedef WrapperAttribute<StringIdentifier> StringIDAttribute_t;

const std::string GAStringIdentifierHeader("$[StringId]");
class StringIdAttrConverter : public E_Utils::AbstractGenericAttributeConverter{
	public:

	virtual ~StringIdAttrConverter(){}
	EScript::String * convertToEScript(const GenericAttribute * const attribute) override {
		const StringIDAttribute_t * objContainer = dynamic_cast<const StringIDAttribute_t *> (attribute);
		return objContainer == nullptr ? nullptr : EScript::create(GAStringIdentifierHeader + objContainer->get().toString());
	}

	GenericAttribute * convertFromEScript(const EScript::ObjPtr & object) override {
		const std::string & s = object.toString();
		if(!StringUtils::beginsWith(s.c_str(), GAStringIdentifierHeader.c_str()))
			return nullptr;
		return GenericAttribute::createUndefined(StringIdentifier(s.substr(GAStringIdentifierHeader.length())));
	}
};

//! (static)
EScript::Type * E_SurfelManager::getTypeObject() {
	// E_SurfelManager ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

//! (static) init members 
void E_SurfelManager::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_SurfelManager::getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	using namespace MinSG;
	using namespace MinSG::ThesisSascha;
	
	// SurfelManager(const Util::FileName& basePath)
	//! [ESF] new SurfelManager(p0)
	ES_CTOR(typeObject,2,2,
				new SurfelManager(Util::FileName(parameter[0].toString()), parameter[1].toUInt()))

	ES_MFUN(typeObject,SurfelManager,"update",0,0,
				(thisObj->update(),thisEObj))

	ES_MFUN(typeObject,SurfelManager,"getPreprocessor",0,0,
				EScript::create(thisObj->getPreprocessor()))

	ES_MFUN(typeObject,SurfelManager,"setBasePath",1,1,
				(thisObj->setBasePath(parameter[0].toString()),thisEObj))

	ES_MFUN(typeObject,SurfelManager,"isCached",1,1,
				EScript::Bool::create(thisObj->isCached(parameter[0].to<Node*>(rt))))

	E_Utils::registerConverter(new StringIdAttrConverter());
}
}

}
#endif // MINSG_EXT_THESISSASCHA

