#pragma once

//#include "GeoSourceJames.g.h"
#include "GeoSourceJames.h"


using namespace winrt;
using namespace Windows::UI::Composition;
using namespace Windows::Foundation::Numerics;

namespace winrt::VectorsCPP::implementation
{
    struct GeoSourceJames //: GeoSourceJamesT<GeoSourceJames>
    {
	private:
		Compositor _compositor;
		ExpressionAnimation _expressionAnimation{ nullptr };
		ExpressionAnimation _expressionAnimation_0000{ nullptr };

		ContainerVisual _containerVisual_0000{ nullptr };
		LinearEasingFunction _linearEasingFunction_0000{ nullptr };
		CompositionColorBrush _compositionColorBrush_0001{ nullptr };

		ShapeVisual ShapeVisual_0000();
		CompositionContainerShape CompositionContainerShape_0000();
		CompositionContainerShape CompositionContainerShape_0001();
		CompositionContainerShape CompositionContainerShape_0002();
		CompositionContainerShape CompositionContainerShape_0003();
		CompositionContainerShape CompositionContainerShape_0004();
		CompositionContainerShape CompositionContainerShape_0005();
		CompositionSpriteShape CompositionSpriteShape_0000();
		CompositionSpriteShape CompositionSpriteShape_0001();
		CompositionColorBrush CompositionColorBrush_0001();
		CompositionColorBrush CompositionColorBrush_0000();
		CompositionPathGeometry CompositionPathGeometry_0000();
		Microsoft::Graphics::Canvas::Geometry::CanvasGeometry CanvasGeometry_0000();
		Vector2KeyFrameAnimation Vector2KeyFrameAnimation_0000();
		LinearEasingFunction LinearEasingFunction_0000();
		ExpressionAnimation ExpressionAnimation_0000();
		CubicBezierEasingFunction CubicBezierEasingFunction_0000();
		CubicBezierEasingFunction CubicBezierEasingFunction_0001();
		CubicBezierEasingFunction CubicBezierEasingFunction_0002();
		CompositionEllipseGeometry CompositionEllipseGeometry_0000();
		ScalarKeyFrameAnimation ScalarKeyFrameAnimation_0000();

		Windows::UI::Composition::ContainerVisual GetRootContainerVisual();
		Windows::UI::Composition::ContainerVisual ContainerVisual_0000();

	public:
		GeoSourceJames();

		int32_t TryCreateInstance(Windows::UI::Composition::Compositor,
			Windows::UI::Composition::Visual&,
			Windows::Foundation::Numerics::float2&,
			Windows::UI::Composition::CompositionPropertySet&,
			Windows::Foundation::TimeSpan&);

        int32_t Dummy();
        void Dummy(int32_t value);
    };
}

//namespace winrt::VectorsCPP::factory_implementation
//{
//	struct GeoSourceJames : GeoSourceJamesT<GeoSourceJames, implementation::GeoSourceJames>
//	{
//	};
//}
