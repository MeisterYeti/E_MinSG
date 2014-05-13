#ifdef MINSG_EXT_THESISSASCHA

#ifndef E_MINSG_THESISSASCHA_E_PREPROCESSOR_H_
#define E_MINSG_THESISSASCHA_E_PREPROCESSOR_H_

#include <EScript/Objects/ExtReferenceObject.h>
#include <MinSG/Ext/ThesisSascha/Preprocessor.h>
#include <E_Util/E_ObjectFactory.h>
#include <E_Util/E_Utils.h>
#include <Util/Factory/WrapperFactory.h>


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
class E_Preprocessor : public EScript::ExtReferenceObject<Util::Reference<MinSG::ThesisSascha::Preprocessor>,EScript::Policies::EqualContent_ComparePolicy,E_Util::Policies::StoreAttrsInAttributeProvider> {
		ES_PROVIDES_TYPE_NAME(Preprocessor)
		static E_Util::E_ObjectFactory<MinSG::ThesisSascha::Preprocessor, E_Preprocessor> factorySystem;
protected:
	template<class Type, class E_Type>
	static void addFactory() {
		factorySystem.registerType(Type::getClassId(), Util::PolymorphicWrapperCreator<MinSG::ThesisSascha::Preprocessor, Type, E_Type>());
	}
	public:
		static E_Preprocessor * create(MinSG::ThesisSascha::Preprocessor * preprocessor) {
			if(preprocessor == nullptr) {
				return nullptr;
			}
			return factorySystem.create(preprocessor->getTypeId(), preprocessor);
		}
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		E_Preprocessor(Util::Reference<MinSG::ThesisSascha::Preprocessor> _obj) :
				ExtReferenceObject_t(getTypeObject(), std::move(_obj)) {}
		virtual ~E_Preprocessor() {}

};
}
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::ThesisSascha::E_Preprocessor, Util::Reference<MinSG::ThesisSascha::Preprocessor>, **eObj)
ES_CONV_EOBJ_TO_OBJ(E_MinSG::ThesisSascha::E_Preprocessor, MinSG::ThesisSascha::Preprocessor *, (**eObj).get())
ES_CONV_OBJ_TO_EOBJ(Util::Reference<MinSG::ThesisSascha::Preprocessor>, E_MinSG::ThesisSascha::E_Preprocessor, obj.isNotNull() ? E_MinSG::ThesisSascha::E_Preprocessor::create(obj.get()) : nullptr)

#endif // E_MINSG_THESISSASCHA_E_PREPROCESSOR_H_
#endif // MINSG_EXT_THESISSASCHA

