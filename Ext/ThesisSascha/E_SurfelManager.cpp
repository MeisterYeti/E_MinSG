#ifdef MINSG_EXT_THESISSASCHA

#include "E_SurfelManager.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

#include <Util/IO/FileName.h>

namespace E_MinSG{
namespace ThesisSascha{


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

	using namespace MinSG::ThesisSascha;
	
	// SurfelManager(const Util::FileName& basePath)
	//! [ESF] new SurfelManager(p0)
	ES_CTOR(typeObject,1,1,
				new SurfelManager(Util::FileName(parameter[0].toString())))

}
}

}
#endif // MINSG_EXT_THESISSASCHA

