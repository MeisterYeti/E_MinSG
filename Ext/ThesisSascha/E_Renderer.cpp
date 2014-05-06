/*
 * E_Renderer.cpp
 *
 *  Created on: May 6, 2014
 *      Author: meisteryeti
 */
#ifdef MINSG_EXT_THESISSASCHA

#include "E_Renderer.h"
#include "E_SurfelManager.h"

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

	addFactory<Renderer,E_Renderer>();

	// SurfelRenderer(Util::StringIdentifier newChannel = MinSG::FrameContext::DEFAULT_CHANNEL)
	//! [ESF] new SurfelRenderer(p0[,p1])
	ES_CONSTRUCTOR(getTypeObject(), 1,2, {
		if(parameter.count()==1)
			return EScript::create(new Renderer(parameter[0].to<SurfelManager*>(rt)));
		else
			return EScript::create(new Renderer(parameter[0].to<SurfelManager*>(rt),parameter[1].to<std::string>(rt)));
	})
}
}

}
#endif // MINSG_EXT_THESISSASCHA
