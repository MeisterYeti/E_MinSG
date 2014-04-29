#ifdef MINSG_EXT_THESISSASCHA

#ifndef E_MINSG_THESISSASCHA_E_SURFELMANAGER_H_
#define E_MINSG_THESISSASCHA_E_SURFELMANAGER_H_

#include <EScript/Objects/ReferenceObject.h>
#include <MinSG/Ext/ThesisSascha/SurfelManager.h>


namespace EScript {
class Namespace;
class Type;
}
namespace E_MinSG{
namespace ThesisSascha{


/*!	EScript wrapper class for MinSG::ThesisSascha::SurfelManager

		E_SurfelManager ---|> EScript::ReferenceObject<Util::Reference<MinSG::ThesisSascha::SurfelManager> >
			|
			--------------> MinSG::ThesisSascha::SurfelManager		*/
class E_SurfelManager : public EScript::ReferenceObject<Util::Reference<MinSG::ThesisSascha::SurfelManager> > {
		ES_PROVIDES_TYPE_NAME(SurfelManager)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		E_SurfelManager(Util::Reference<MinSG::ThesisSascha::SurfelManager> _obj) :
				ReferenceObject_t(getTypeObject(), std::move(_obj)) {}
		virtual ~E_SurfelManager() {}

};
}
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::ThesisSascha::E_SurfelManager, Util::Reference<MinSG::ThesisSascha::SurfelManager>, **eObj)
ES_CONV_EOBJ_TO_OBJ(E_MinSG::ThesisSascha::E_SurfelManager, MinSG::ThesisSascha::SurfelManager *, (**eObj).get())
ES_CONV_OBJ_TO_EOBJ(Util::Reference<MinSG::ThesisSascha::SurfelManager>, E_MinSG::ThesisSascha::E_SurfelManager, new E_MinSG::ThesisSascha::E_SurfelManager(obj))

#endif // E_MINSG_THESISSASCHA_E_SURFELMANAGER_H_
#endif // MINSG_EXT_THESISSASCHA

