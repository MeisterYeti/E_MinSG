#ifdef MINSG_EXT_THESISSASCHA

#include "E_Preprocessor.h"
#include "E_SurfelManager.h"

#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

#include <E_MinSG/Core/Nodes/E_Node.h>
#include <E_MinSG/Core/E_FrameContext.h>

#include <Util/IO/FileName.h>

namespace E_MinSG{
namespace ThesisSascha{


//! (static)
EScript::Type * E_Preprocessor::getTypeObject() {
	// E_SurfelManager ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

//! (static) init members
void E_Preprocessor::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_Preprocessor::getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	using namespace Util;
	using namespace MinSG;
	using namespace MinSG::ThesisSascha;

	// Preprocessor(SurfelManager* manager)
	//! [ESF] new Preprocessor(p0)
	ES_CTOR(typeObject,1,1,
				new Preprocessor(parameter[0].to<SurfelManager*>(rt)))

	// void initialize(const Util::FileName& helperShader, const Util::FileName& positionShader, const Util::FileName& normalShader, const Util::FileName& colorShader, const Util::FileName& sizeShader)
	//! [ESMF] self Preprocessor.initialize(p0,p1,p2,p3,p4)
	ES_MFUN(typeObject,Preprocessor,"initialize",5,5,
				(thisObj->initialize(FileName(parameter[0].toString()),FileName(parameter[1].toString()),FileName(parameter[2].toString()),FileName(parameter[3].toString()),FileName(parameter[4].toString())),thisEObj))

	// void process(FrameContext& frameContext, Node* root)
	//! [ESMF] self Preprocessor.process(p0,p1)
	ES_MFUN(typeObject,Preprocessor,"process",2,2,
				(thisObj->process(parameter[0].to<FrameContext&>(rt),parameter[1].to<Node*>(rt)),thisEObj))

}
}

}
#endif // MINSG_EXT_THESISSASCHA
