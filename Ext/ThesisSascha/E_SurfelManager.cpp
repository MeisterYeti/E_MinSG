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
	ES_CTOR(typeObject,3,3,
				new SurfelManager(Util::FileName(parameter[0].toString()), parameter[1].toUInt(), parameter[2].toUInt()))

	ES_MFUN(typeObject,SurfelManager,"update",0,0,
				(thisObj->update(),thisEObj))

	ES_MFUN(typeObject,SurfelManager,"clear",0,0,
				(thisObj->clear(),thisEObj))

	ES_MFUN(typeObject,SurfelManager,"flush",0,0,
				(thisObj->flush(),thisEObj))

	ES_MFUN(typeObject,SurfelManager,"getPreprocessor",0,0,
				EScript::create(thisObj->getPreprocessor()))

	ES_MFUN(typeObject,SurfelManager,"setBasePath",1,1,
				(thisObj->setBasePath(parameter[0].toString()),thisEObj))

	ES_MFUN(typeObject,SurfelManager,"isCached",1,1,
				EScript::Bool::create(thisObj->isCached(parameter[0].to<Node*>(rt))))

	ES_MFUN(typeObject,SurfelManager,"getMaxMemory",0,0,
				EScript::Number::create(thisObj->getMaxMemory()))

	ES_MFUN(typeObject,SurfelManager,"setRequestLimit",1,1,
				(thisObj->setRequestLimit(parameter[0].toUInt()),thisEObj))

	ES_MFUN(typeObject,SurfelManager,"setMaxMemory",1,1,
				(thisObj->setMaxMemory(parameter[0].toUInt()),thisEObj))

	ES_MFUN(typeObject,SurfelManager,"setFrameRequestLimit",1,1,
				(thisObj->setFrameRequestLimit(parameter[0].toUInt()),thisEObj))

	ES_MFUN(typeObject,SurfelManager,"setMaxPending",1,1,
				(thisObj->setMaxPending(parameter[0].toUInt()),thisEObj))

	ES_MFUN(typeObject,SurfelManager,"getMemoryLoadFactor",0,0,
				EScript::Number::create(thisObj->getMemoryLoadFactor()))

	ES_MFUN(typeObject,SurfelManager,"setMemoryLoadFactor",1,1,
				(thisObj->setMemoryLoadFactor(parameter[0].toFloat()),thisEObj))

	ES_MFUN(typeObject,SurfelManager,"setSortRequests",1,1,
				(thisObj->setSortRequests(parameter[0].toBool()),thisEObj))

	ES_MFUN(typeObject,SurfelManager,"setMaxIter",1,1,
				(thisObj->setMaxIter(parameter[0].toUInt()),thisEObj))

	ES_MFUN(typeObject,SurfelManager,"getStats",0,0,E_Util::E_Utils::convertGenericAttributeToEScriptObject(thisObj->getStats()))

	{
		struct ScriptedFunction{
			EScript::Runtime & rt;
			SurfelManager * owner;
			ScriptedFunction(EScript::Runtime & _rt, SurfelManager * _owner) : rt(_rt), owner(_owner){}
			float operator()(StringIdentifier id, uint32_t lru, uint32_t usage,
			 				uint32_t memory, uint32_t childCount, float projSize,
			 				float minDistance, bool isSurfel){
				static const EScript::StringId handlerId("requestPriorityFn");
				EScript::ParameterValues params(8);
				uint32_t i = 0;
				params.set(i++,EScript::create(id.toString()));
				params.set(i++,EScript::create(lru));
				params.set(i++,EScript::create(usage));
				params.set(i++,EScript::create(memory));
				params.set(i++,EScript::create(childCount));
				params.set(i++,EScript::create(projSize));
				params.set(i++,EScript::create(minDistance));
				params.set(i++,EScript::create(isSurfel));
				EScript::ObjRef result = EScript::callMemberFunction(rt,EScript::create(owner),handlerId, params);
				return result.toFloat(0);
			}
		};

		ES_MFUN(getTypeObject(),SurfelManager,"enableRequestPriorityFn",0,0,
					(thisObj->setRequestPriorityFn(std::move(ScriptedFunction(rt,thisObj))),thisEObj))
	}

}
}

}
#endif // MINSG_EXT_THESISSASCHA

