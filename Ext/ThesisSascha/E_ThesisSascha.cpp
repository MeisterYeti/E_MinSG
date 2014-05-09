/*
 * E_ThesisSascha.cpp
 *
 *  Created on: May 9, 2014
 *      Author: meisteryeti
 */
#ifdef MINSG_EXT_THESISSASCHA

#include "E_ThesisSascha.h"

#include "E_Preprocessor.h"
#include "E_SurfelManager.h"
#include "E_Renderer.h"

#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

#include <MinSG/Ext/ThesisSascha/ImportHandler.h>

#include <Util/StringUtils.h>
#include <Util/Macros.h>

namespace E_MinSG {
namespace ThesisSascha {

void init(EScript::Namespace & lib) {
	using namespace MinSG::ThesisSascha;
	EScript::Namespace * ns = new EScript::Namespace;
	declareConstant(&lib, "ThesisSascha", ns);
	ThesisSascha::E_SurfelManager::init(*ns);
	ThesisSascha::E_Preprocessor::init(*ns);
	ThesisSascha::E_Renderer::init(*ns);

	//! [ESF] Void MinSG.ThesisSascha.pushImportHandler(SurfelManager)
	ES_FUN(ns, "pushImportHandler", 1, 1, (ImportHandler::pushImportHandler(parameter[0].to<SurfelManager*>(rt)), EScript::create(nullptr)))

	//! [ESF] Void MinSG.ThesisSascha.popImportHandler()
	ES_FUN(ns, "popImportHandler", 0, 0, (ImportHandler::popImportHandler(), EScript::create(nullptr)))
}

}
}

#endif /* MINSG_EXT_THESISSASCHA */
