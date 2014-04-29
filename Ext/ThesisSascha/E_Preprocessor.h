#ifdef MINSG_EXT_THESISSASCHA

#ifndef E_MINSG_THESISSASCHA_E_PREPROCESSOR_H_
#define E_MINSG_THESISSASCHA_E_PREPROCESSOR_H_

#include <EScript/Objects/ReferenceObject.h>
#include <MinSG/Ext/ThesisSascha/Preprocessor.h>


namespace EScript {
class Namespace;
class Type;
}
namespace E_MinSG{
namespace ThesisSascha{


/*!	EScript wrapper class for MinSG::ThesisSascha::SurfelManager

		E_Preprocessor ---|> EScript::ReferenceObject<Util::Reference<MinSG::ThesisSascha::Preprocessor> >
			|
			--------------> MinSG::ThesisSascha::SurfelManager		*/
class E_Preprocessor : public EScript::ReferenceObject<Util::Reference<MinSG::ThesisSascha::Preprocessor> > {
		ES_PROVIDES_TYPE_NAME(Preprocessor)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		E_Preprocessor(Util::Reference<MinSG::ThesisSascha::Preprocessor> _obj) :
				ReferenceObject_t(getTypeObject(), std::move(_obj)) {}
		virtual ~E_Preprocessor() {}

};
}
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::ThesisSascha::E_Preprocessor, Util::Reference<MinSG::ThesisSascha::Preprocessor>, **eObj)
ES_CONV_EOBJ_TO_OBJ(E_MinSG::ThesisSascha::E_Preprocessor, MinSG::ThesisSascha::Preprocessor *, (**eObj).get())
ES_CONV_OBJ_TO_EOBJ(Util::Reference<MinSG::ThesisSascha::Preprocessor>, E_MinSG::ThesisSascha::E_Preprocessor, new E_MinSG::ThesisSascha::E_Preprocessor(obj))

#endif // E_MINSG_THESISSASCHA_E_PREPROCESSOR_H_
#endif // MINSG_EXT_THESISSASCHA

