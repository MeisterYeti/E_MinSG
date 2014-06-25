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

#include <MinSG/Ext/ThesisSascha/Definitions.h>
#include <MinSG/Ext/ThesisSascha/ImportHandler.h>

#include <Util/IO/FileUtils.h>
#include <Util/IO/FileName.h>
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

	declareConstant(ns, "SURFEL_ID", EScript::String::create(SURFEL_ID.toString()));
	declareConstant(ns, "SURFEL_STRINGID", EScript::String::create(SURFEL_STRINGID.toString()));
	declareConstant(ns, "SURFEL_REL_COVERING", EScript::String::create(SURFEL_REL_COVERING.toString()));
	declareConstant(ns, "SURFEL_COUNT", EScript::String::create(SURFEL_COUNT.toString()));
	declareConstant(ns, "SURFELS", EScript::String::create(SURFELS.toString()));
	declareConstant(ns, "MESH_ID", EScript::String::create(MESH_ID.toString()));
	declareConstant(ns, "MESH_STRINGID", EScript::String::create(MESH_STRINGID.toString()));
	declareConstant(ns, "MESH_COMPLEXITY", EScript::String::create(MESH_COMPLEXITY.toString()));
	declareConstant(ns, "NODE_COMPLEXITY", EScript::String::create(NODE_COMPLEXITY.toString()));
	declareConstant(ns, "NODE_LEVEL", EScript::String::create(NODE_LEVEL.toString()));
	declareConstant(ns, "NODE_HANDLED", EScript::String::create(NODE_HANDLED.toString()));
	declareConstant(ns, "CHILDREN_LOADED", EScript::String::create(CHILDREN_LOADED.toString()));

	//! [ESF] Void MinSG.ThesisSascha.pushImportHandler(SurfelManager)
	ES_FUN(ns, "pushImportHandler", 1, 1, (ImportHandler::pushImportHandler(parameter[0].to<SurfelManager*>(rt)), EScript::create(nullptr)))

	//! [ESF] Void MinSG.ThesisSascha.popImportHandler()
	ES_FUN(ns, "popImportHandler", 0, 0, (ImportHandler::popImportHandler(), EScript::create(nullptr)))

	ES_FUN(ns, "generateId", 0, 1, EScript::String::create(Util::StringUtils::createRandomString(parameter[0].toUInt(32))))

	//! [ESF] Bool MinSG.ThesisSascha.moveFile(String, String)
	ES_FUNCTION(ns, "moveFile", 2, 2, {
		bool result = Util::FileUtils::copyFile(Util::FileName(parameter[0].toString()), Util::FileName(parameter[1].toString()));
		if(result)
			Util::FileUtils::remove(Util::FileName(parameter[0].toString()));
		return EScript::Bool::create(result);
	})
	//! [ESF] Bool MinSG.ThesisSascha.removeFile(String, String)
	ES_FUN(ns, "removeFile", 1, 1, EScript::Bool::create(Util::FileUtils::remove(Util::FileName(parameter[0].toString()))))
}

}
}

#endif /* MINSG_EXT_THESISSASCHA */
