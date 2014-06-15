#ifdef MINSG_EXT_THESISSASCHA

#include "E_Preprocessor.h"
#include "E_SurfelManager.h"

#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

#include <E_MinSG/Core/Nodes/E_Node.h>
#include <E_MinSG/Core/E_FrameContext.h>

#include <E_Rendering/Shader/E_Shader.h>

#include <Util/IO/FileName.h>

namespace E_MinSG{
namespace ThesisSascha{

//! (static)
E_Util::E_ObjectFactory<MinSG::ThesisSascha::Preprocessor,E_Preprocessor> E_Preprocessor::factorySystem;

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
	addFactory<MinSG::ThesisSascha::Preprocessor,E_Preprocessor>();

	using namespace Util;
	using namespace MinSG;
	using namespace MinSG::ThesisSascha;

	// void initShader(Rendering::Shader* mrtShader, Rendering::Shader* sizeShader)
	//! [ESMF] self Preprocessor.initShader(p0,p1)
	ES_MFUN(typeObject,Preprocessor,"initShader",2,2,
				(thisObj->initShaders(parameter[0].to<Rendering::Shader*>(rt), parameter[1].to<Rendering::Shader*>(rt)),thisEObj))

	// void process(FrameContext& frameContext, Node* root)
	//! [ESMF] self Preprocessor.process(p0,p1)
	ES_MFUN(typeObject,Preprocessor,"process",2,3,
				(thisObj->process(parameter[0].to<FrameContext&>(rt),parameter[1].to<Node*>(rt),parameter[2].toBool(true)),thisEObj))

	{
		struct ScriptedFunction{
			EScript::Runtime & rt;
			Preprocessor * owner;
			ScriptedFunction(EScript::Runtime & _rt, Preprocessor * _owner) : rt(_rt), owner(_owner){}
			bool operator()(Node * node, float coverage){
				static const EScript::StringId handlerId("abortUpdate");
				EScript::ObjRef result = EScript::callMemberFunction(rt,EScript::create(owner),handlerId,
															EScript::ParameterValues(EScript::create(node), EScript::Number::create(coverage)));
				return result.toBool(true);
			}
		};

		ES_MFUN(typeObject,Preprocessor,"enableAbortUpdateFn",0,0,
					(thisObj->setAbortUpdateFn(std::move(ScriptedFunction(rt,thisObj))),thisEObj))
	}

	{
		struct ScriptedFunction{
			EScript::Runtime & rt;
			Preprocessor * owner;
			ScriptedFunction(EScript::Runtime & _rt, Preprocessor * _owner) : rt(_rt), owner(_owner){}
			void operator()(uint32_t done, uint32_t maxCount){
				static const EScript::StringId handlerId("updateProgress");
				EScript::ObjRef result = EScript::callMemberFunction(rt,EScript::create(owner),handlerId,
															EScript::ParameterValues(EScript::Number::create(done), EScript::Number::create(maxCount)));
			}
		};

		ES_MFUN(typeObject,Preprocessor,"enableUpdateProgressFn",0,0,
					(thisObj->setUpdateProgressFn(std::move(ScriptedFunction(rt,thisObj))),thisEObj))
	}

	ES_MFUN(typeObject,Preprocessor,"updateSurfels",2,3,
				(thisObj->updateSurfels(parameter[0].to<FrameContext&>(rt),parameter[1].to<Node*>(rt), 1.0f, parameter[2].toBool(false)),thisEObj))



	//! [ESMF] Number Preprocessor.getReusalRate()
	ES_MFUN(typeObject,const Preprocessor,"getReusalRate",0,0,			thisObj->getReusalRate())

	//! [ESMF] Number Preprocessor.getMaxAbsSurfels()
	ES_MFUN(typeObject,const Preprocessor,"getMaxAbsSurfels",0,0,		thisObj->getMaxAbsSurfels())

	//! [ESMF] self Preprocessor.setMaxAbsSurfels(Number)
	ES_MFUN(typeObject,Preprocessor,"setMaxAbsSurfels",1,1,				(thisObj->setMaxAbsSurfels(parameter[0].toUInt()),thisEObj))

	//! [ESMF] self Preprocessor.setReusalRate(Number)
	ES_MFUN(typeObject,Preprocessor,"setReusalRate",1,1,					(thisObj->setReusalRate(parameter[0].toFloat()),thisEObj))

	//! [ESMF] self Preprocessor.setMaxComplexity(Number)
	ES_MFUN(typeObject,Preprocessor,"setMaxComplexity",1,1,				(thisObj->setMaxComplexity(parameter[0].toUInt()),thisEObj))
}
}

}
#endif // MINSG_EXT_THESISSASCHA
