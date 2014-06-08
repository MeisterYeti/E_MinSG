/*
 * E_Renderer.cpp
 *
 *  Created on: May 6, 2014
 *      Author: meisteryeti
 */
#ifdef MINSG_EXT_THESISSASCHA

#include "E_Renderer.h"
#include "E_SurfelManager.h"

#include <E_MinSG/Core/Nodes/E_Node.h>
#include <MinSG/Core/Nodes/Node.h>

#include <EScript/Basics.h>
#include <EScript/StdObjects.h>


namespace E_MinSG {
namespace ThesisSascha {

//! (static)
EScript::Type * E_Renderer::getTypeObject() {
	// E_Renderer ---|> [E_NodeRendererState] ---|> [E_State] ---|> [ReferenceObject]
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_NodeRendererState::getTypeObject());
	return typeObject.get();
}

//! (static) init members
void E_Renderer::init(EScript::Namespace & lib) {

	using namespace Util;
	using namespace MinSG;
	using namespace MinSG::ThesisSascha;

	declareConstant(&lib, E_Renderer::getClassName(), getTypeObject());

	declareConstant(getTypeObject(),"SKIP",EScript::Number::create(static_cast<int>(Renderer::Skip)));
	declareConstant(getTypeObject(),"SKIP_CHILDREN",EScript::Number::create(static_cast<int>(Renderer::SkipChildren)));
	declareConstant(getTypeObject(),"REFINE_AND_SKIP",EScript::Number::create(static_cast<int>(Renderer::RefineAndSkip)));
	declareConstant(getTypeObject(),"REFINE_AND_CONTINUE",EScript::Number::create(static_cast<int>(Renderer::RefineAndContinue)));

	addFactory<Renderer,E_Renderer>();

	// SurfelRenderer(Util::StringIdentifier newChannel = MinSG::FrameContext::DEFAULT_CHANNEL)
	//! [ESF] new SurfelRenderer(p0[,p1])
	ES_CONSTRUCTOR(getTypeObject(), 1,2, {
		if(parameter.count()==1)
			return EScript::create(new Renderer(parameter[0].to<SurfelManager*>(rt)));
		else
			return EScript::create(new Renderer(parameter[0].to<SurfelManager*>(rt),parameter[1].to<std::string>(rt)));
	})

	ES_MFUN(getTypeObject(),Renderer,"setAsync",1,1,
				(thisObj->setAsync(parameter[0].toBool(false)),thisEObj))

	ES_MFUN(getTypeObject(),Renderer,"isAsync",0,0,
				EScript::Bool::create(thisObj->isAsync()))

	ES_MFUN(getTypeObject(),Renderer,"setImmediate",1,1,
				(thisObj->setImmediate(parameter[0].toBool(false)),thisEObj))

	ES_MFUN(getTypeObject(),Renderer,"isImmediate",0,0,
				EScript::Bool::create(thisObj->isImmediate()))

	ES_MFUN(getTypeObject(),Renderer,"setTimeLimit",1,1,
				(thisObj->setTimeLimit(parameter[0].toUInt(0)),thisEObj))

	ES_MFUN(getTypeObject(),Renderer,"getTimeLimit",0,0,
				EScript::Number::create(thisObj->getTimeLimit()))

	{
		struct ScriptedFunction{
			EScript::Runtime & rt;
			Renderer * owner;
			ScriptedFunction(EScript::Runtime & _rt, Renderer * _owner) : rt(_rt), owner(_owner){}
			Renderer::RefineNode_t operator()(Node * node){
				static const EScript::StringId handlerId("refineNode");
				EScript::ObjRef result = EScript::callMemberFunction(rt,EScript::create(owner),handlerId,
															EScript::ParameterValues(EScript::create(node)));
				return static_cast<Renderer::RefineNode_t>(result.toInt(0));
			}
		};

		ES_MFUN(getTypeObject(),Renderer,"enableRefineFn",0,0,
					(thisObj->setRefineFn(std::move(ScriptedFunction(rt,thisObj))),thisEObj))
	}

	{
		struct ScriptedFunction{
			EScript::Runtime & rt;
			Renderer * owner;
			ScriptedFunction(EScript::Runtime & _rt, Renderer * _owner) : rt(_rt), owner(_owner){}
			uint32_t operator()(Node * node, float size, uint32_t maxCount, float coverage){
				static const EScript::StringId handlerId("countSurfels");
				EScript::ObjRef result = EScript::callMemberFunction(rt,EScript::create(owner),handlerId,
															EScript::ParameterValues(EScript::create(node),
																	EScript::create(size),
																	EScript::create(maxCount),
																	EScript::create(coverage)));
				return result.toUInt();
			}
		};

		ES_MFUN(getTypeObject(),Renderer,"enableCountFn",0,0,
					(thisObj->setCountFn(std::move(ScriptedFunction(rt,thisObj))),thisEObj))
	}

	{
		struct ScriptedFunction{
			EScript::Runtime & rt;
			Renderer * owner;
			ScriptedFunction(EScript::Runtime & _rt, Renderer * _owner) : rt(_rt), owner(_owner){}
			float operator()(Node * node, float size, uint32_t maxCount, float coverage){
				static const EScript::StringId handlerId("surfelSize");
				EScript::ObjRef result = EScript::callMemberFunction(rt,EScript::create(owner),handlerId,
															EScript::ParameterValues(EScript::create(node),
																	EScript::create(size),
																	EScript::create(maxCount),
																	EScript::create(coverage)));
				return result.toFloat(1);
			}
		};

		ES_MFUN(getTypeObject(),Renderer,"enableSizeFn",0,0,
					(thisObj->setSizeFn(std::move(ScriptedFunction(rt,thisObj))),thisEObj))
	}

}
}

}
#endif // MINSG_EXT_THESISSASCHA
