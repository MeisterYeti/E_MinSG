
#ifdef MINSG_EXT_THESISSASCHA
#ifndef E_MINSG_THESISSASCHA_E_RENDERER_H_
#define E_MINSG_THESISSASCHA_E_RENDERER_H_

#include <MinSG/Ext/ThesisSascha/Renderer.h>
#include "../../Core/States/E_NodeRendererState.h"

namespace EScript {
class Namespace;
class Type;
}
namespace E_MinSG {
namespace ThesisSascha {


/*!	EScript wrapper class for MinSG::ThesisSascha::Renderer
	E_Renderer ---|> E_NodeRendererState ---|> EScript::ReferenceObject < MinSG::MAR::SurfelRenderer >
		|
		--------------> MinSG::ThesisSascha::Renderer ---|> MinSG::NodeRendererState
*/
class E_Renderer : public E_NodeRendererState {
		ES_PROVIDES_TYPE_NAME(Renderer)

	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		virtual ~E_Renderer() = default;

		const MinSG::ThesisSascha::Renderer * operator*()const	{ return static_cast<const MinSG::ThesisSascha::Renderer *>(ref().get()); }
		MinSG::ThesisSascha::Renderer * operator*()				{ return static_cast<MinSG::ThesisSascha::Renderer *>(ref().get()); }

	protected:
		E_Renderer(MinSG::ThesisSascha::Renderer * _obj, EScript::Type * type = nullptr) : E_NodeRendererState(_obj, type ? type : E_Renderer::getTypeObject()) {}
};
}
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::ThesisSascha::E_Renderer, MinSG::ThesisSascha::Renderer *, **eObj)

#endif // E_MINSG_THESISSASCHA_E_RENDERER_H_
#endif // MINSG_EXT_THESISSASCHA

