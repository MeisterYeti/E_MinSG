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
	EScript::Type * typeObject = E_Renderer::getTypeObject();

	using namespace Util;
	using namespace MinSG;
	using namespace MinSG::ThesisSascha;

	declareConstant(&lib, E_Renderer::getClassName(), typeObject);

	//declareConstant(getTypeObject(),"SKIP",EScript::Number::create(static_cast<int>(Renderer::Skip)));
	//declareConstant(getTypeObject(),"SKIP_CHILDREN",EScript::Number::create(static_cast<int>(Renderer::SkipChildren)));
	//declareConstant(getTypeObject(),"REFINE_AND_SKIP",EScript::Number::create(static_cast<int>(Renderer::RefineAndSkip)));
	//declareConstant(getTypeObject(),"REFINE_AND_CONTINUE",EScript::Number::create(static_cast<int>(Renderer::RefineAndContinue)));

	addFactory<Renderer,E_Renderer>();

	// SurfelRenderer(Util::StringIdentifier newChannel = MinSG::FrameContext::DEFAULT_CHANNEL)
	//! [ESF] new SurfelRenderer(p0[,p1])
	ES_CONSTRUCTOR(typeObject, 1,2, {
		if(parameter.count()==1)
			return EScript::create(new Renderer(parameter[0].to<SurfelManager*>(rt)));
		else
			return EScript::create(new Renderer(parameter[0].to<SurfelManager*>(rt),parameter[1].to<std::string>(rt)));
	})

	ES_MFUN(typeObject,Renderer,"setPointSizeFactor",1,1,
				(thisObj->setPointSizeFactor(parameter[0].toFloat()),thisEObj))

	ES_MFUN(typeObject,Renderer,"setMinProjSize",1,1,
				(thisObj->setMinProjSize(parameter[0].toFloat()),thisEObj))

	ES_MFUN(typeObject,Renderer,"setSortFront",1,1,
				(thisObj->sortFront(parameter[0].toBool()),thisEObj))

	ES_MFUN(typeObject,Renderer,"setUseFrontRenderer",1,1,
				(thisObj->useFrontRenderer(parameter[0].toBool()),thisEObj))

	ES_MFUN(typeObject,Renderer,"setIncludeDistance",1,1,
				(thisObj->includeDistance(parameter[0].toBool()),thisEObj))

	/*
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

	ES_MFUN(getTypeObject(),Renderer,"setMaxComplexity",1,1,
				(thisObj->setMaxComplexity(parameter[0].toUInt(0)),thisEObj))

	ES_MFUN(getTypeObject(),Renderer,"getMaxComplexity",0,0,
				EScript::Number::create(thisObj->getMaxComplexity()))

	ES_MFUN(getTypeObject(),Renderer,"getRenderTime",0,0,
				EScript::Number::create(thisObj->getRenderTime()))

	ES_MFUN(getTypeObject(),Renderer,"getTraversalTime",0,0,
				EScript::Number::create(thisObj->getTraversalTime()))

	ES_MFUN(getTypeObject(),Renderer,"setWait",1,1,
				(thisObj->setWait(parameter[0].toBool(false)),thisEObj))

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
	*/

	ES_MFUN(typeObject,Renderer,"getStats",0,0,E_Util::E_Utils::convertGenericAttributeToEScriptObject(thisObj->getStats()))
}
}

}
#endif // MINSG_EXT_THESISSASCHA
