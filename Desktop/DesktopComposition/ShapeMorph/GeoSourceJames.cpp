#include "pch.h"
#include "GeoSourceJames.h"

namespace winrt::VectorsCPP::implementation
{
	GeoSourceJames::GeoSourceJames()
	{
	
	}

    int32_t GeoSourceJames::TryCreateInstance(Windows::UI::Composition::Compositor compositor,
		Windows::UI::Composition::Visual& rootVisual,
		float2& size,
		Windows::UI::Composition::CompositionPropertySet& progressPropertySet,
		Windows::Foundation::TimeSpan& duration)
    {
		_compositor = compositor;
		
		_expressionAnimation = compositor.CreateExpressionAnimation();

		rootVisual = GetRootContainerVisual();
		size = { 60, 60 };
		progressPropertySet = rootVisual.Properties();
		duration = Windows::Foundation::TimeSpan(10010000L);

		return true;
    }

	ContainerVisual GeoSourceJames::GetRootContainerVisual()
	{
		return ContainerVisual_0000();
	}

	ContainerVisual GeoSourceJames::ContainerVisual_0000()
	{
		if (_containerVisual_0000 != nullptr)
		{
			return _containerVisual_0000;
		}
		auto result = _containerVisual_0000 = _compositor.CreateContainerVisual();
		auto propertySet = result.Properties();
		propertySet.InsertScalar(L"Progress", 0);
		auto children = result.Children();
		children.InsertAtTop(ShapeVisual_0000());
		return result;
	}

	ShapeVisual GeoSourceJames::ShapeVisual_0000()
	{
		auto result = _compositor.CreateShapeVisual();
		result.Size(float2(60, 60));
		auto shapes = result.Shapes();
		shapes.Append(CompositionContainerShape_0000());
		shapes.Append(CompositionContainerShape_0003());
		return result;
	}

	CompositionContainerShape GeoSourceJames::CompositionContainerShape_0000()
	{
		auto result = _compositor.CreateContainerShape();
		result.Offset(float2(30, 29.25F));
		result.Scale(float2(0.17895F, 0.17895F));
		auto shapes = result.Shapes();
		shapes.Append(CompositionContainerShape_0001());
		result.StartAnimation(L"Scale", Vector2KeyFrameAnimation_0000());
		auto controller = result.TryGetAnimationController(L"Scale");
		controller.Pause();
		controller.StartAnimation(L"Progress", ExpressionAnimation_0000());
		return result;
	}

	CompositionContainerShape GeoSourceJames::CompositionContainerShape_0001()
	{
		auto result = _compositor.CreateContainerShape();
		auto shapes = result.Shapes();
		shapes.Append(CompositionContainerShape_0002());
		_expressionAnimation.ClearAllParameters();
		_expressionAnimation.Expression(L"(_.Progress < 0.03333334) ? (Matrix3x2(0,0,0,0,0,0)) : (Matrix3x2(1,0,0,1,0,0))");
		_expressionAnimation.SetReferenceParameter(L"_", ContainerVisual_0000());
		result.StartAnimation(L"TransformMatrix", _expressionAnimation);
		return result;
	}

	CompositionContainerShape GeoSourceJames::CompositionContainerShape_0002()
	{
		auto result = _compositor.CreateContainerShape();
		result.Offset(float2(0, 0.75F));
		auto shapes = result.Shapes();
		shapes.Append(CompositionSpriteShape_0000());
		return result;
	}

	CompositionContainerShape GeoSourceJames::CompositionContainerShape_0003()
	{
		auto result = _compositor.CreateContainerShape();
		result.Offset(float2(30, 30));
		auto shapes = result.Shapes();
		shapes.Append(CompositionContainerShape_0004());
		return result;
	}

	CompositionContainerShape GeoSourceJames::CompositionContainerShape_0004()
	{
		auto result = _compositor.CreateContainerShape();
		auto shapes = result.Shapes();
		shapes.Append(CompositionContainerShape_0005());
		_expressionAnimation.ClearAllParameters();
		_expressionAnimation.Expression(L"(_.Progress < 0.1) ? (Matrix3x2(0,0,0,0,0,0)) : (Matrix3x2(1,0,0,1,0,0))");
		_expressionAnimation.SetReferenceParameter(L"_", ContainerVisual_0000());
		result.StartAnimation(L"TransformMatrix", _expressionAnimation);
		return result;
	}

	CompositionContainerShape GeoSourceJames::CompositionContainerShape_0005()
	{
		auto result = _compositor.CreateContainerShape();
		auto shapes = result.Shapes();
		shapes.Append(CompositionSpriteShape_0001());
		return result;
	}

	CompositionSpriteShape GeoSourceJames::CompositionSpriteShape_0000()
	{
		auto result = _compositor.CreateSpriteShape();
		result.FillBrush(CompositionColorBrush_0000());
		result.Geometry(CompositionEllipseGeometry_0000());
		result.StrokeBrush(CompositionColorBrush_0001());
		result.StrokeMiterLimit(4);
		result.StrokeThickness(3);
		return result;
	}

	CompositionSpriteShape GeoSourceJames::CompositionSpriteShape_0001()
	{
		auto result = _compositor.CreateSpriteShape();
		result.Geometry(CompositionPathGeometry_0000());
		result.StrokeBrush(CompositionColorBrush_0001());
		result.StrokeMiterLimit(4);
		result.StrokeThickness(7);
		return result;
	}

	CompositionColorBrush GeoSourceJames::CompositionColorBrush_0000()
	{
		return _compositor.CreateColorBrush({ 0xFF, 0x7E, 0xD3, 0x21 });
	}

	CompositionColorBrush GeoSourceJames::CompositionColorBrush_0001()
	{
		if (_compositionColorBrush_0001 != nullptr)
		{
			return _compositionColorBrush_0001;
		}
		auto result = _compositionColorBrush_0001 = _compositor.CreateColorBrush({ 0xFF, 0xFF, 0xFF, 0xFF });
		return result;
	}

	CompositionEllipseGeometry GeoSourceJames::CompositionEllipseGeometry_0000()
	{
		auto result = _compositor.CreateEllipseGeometry();
		result.Radius(float2(29.698F, 29.698F));
		return result;
	}

	CompositionPathGeometry GeoSourceJames::CompositionPathGeometry_0000()
	{
		auto path = CanvasGeometry_0000();
		auto compositionPath = CompositionPath(path);
		auto result = _compositor.CreatePathGeometry(compositionPath);
		result.TrimEnd(0);
		result.StartAnimation(L"TrimEnd", ScalarKeyFrameAnimation_0000());
		auto controller = result.TryGetAnimationController(L"TrimEnd");
		controller.Pause();
		controller.StartAnimation(L"Progress", ExpressionAnimation_0000());
		return result;
	}

	ScalarKeyFrameAnimation GeoSourceJames::ScalarKeyFrameAnimation_0000()
	{
		auto result = _compositor.CreateScalarKeyFrameAnimation();
		result.Duration(Windows::Foundation::TimeSpan{ 10010000L });
		result.InsertKeyFrame(0, 0, LinearEasingFunction_0000());
		result.InsertKeyFrame(0.1F, 0, LinearEasingFunction_0000());
		result.InsertKeyFrame(0.4666667F, 1, CubicBezierEasingFunction_0002());
		return result;
	}

	Microsoft::Graphics::Canvas::Geometry::CanvasGeometry GeoSourceJames::CanvasGeometry_0000()
	{
		/*ComPtr<ID2D1PathGeometry> path;
		_d2dFactory->CreatePathGeometry(&path);
		ComPtr<ID2D1GeometrySink> sink;
		path->Open(&sink);
		sink->BeginFigure({ -14.75F, -3 }, D2D1_FIGURE_BEGIN_FILLED);
		sink->AddBezier({ { -14.75F, -3 },{ -1.25F, 8.25F },{ -1.25F, 8.25F } });
		sink->AddBezier({ { -1.25F, 8.25F },{ 14.25F, -11.25F },{ 14.25F, -11.25F } });
		sink->EndFigure(D2D1_FIGURE_END_OPEN);
		sink->Close();
		return D2DPathGeometryToIGeometrySource2D(path);*/

		auto defaultDevice = Microsoft::Graphics::Canvas::CanvasDevice::GetSharedDevice();
		auto pathBuilder = Microsoft::Graphics::Canvas::Geometry::CanvasPathBuilder(defaultDevice);
		pathBuilder.BeginFigure( -14.75F, -3);
		pathBuilder.AddCubicBezier( float2( -14.75F, -3 ),float2( -1.25F, 8.25F ),float2( -1.25F, 8.25F ) );
		pathBuilder.AddCubicBezier( float2( -1.25F, 8.25F), float2( 14.25F, -11.25F ), float2( 14.25F, -11.25F ) );
		pathBuilder.EndFigure(Microsoft::Graphics::Canvas::Geometry::CanvasFigureLoop::Open);
		auto finalGeo = Microsoft::Graphics::Canvas::Geometry::CanvasGeometry::CreatePath(pathBuilder);
		return finalGeo;
	}

	Vector2KeyFrameAnimation GeoSourceJames::Vector2KeyFrameAnimation_0000()
	{
		auto result = _compositor.CreateVector2KeyFrameAnimation();
		result.Duration(Windows::Foundation::TimeSpan(10010000L));
		result.InsertKeyFrame(0, float2(0.17895F, 0.17895F), LinearEasingFunction_0000());
		result.InsertKeyFrame(0.03333334F, float2(0.17895F, 0.17895F), LinearEasingFunction_0000());
		result.InsertKeyFrame(0.3666667F, float2(0.94836F, 0.94836F), CubicBezierEasingFunction_0000());
		result.InsertKeyFrame(0.7333333F, float2(0.88847F, 0.88847F), CubicBezierEasingFunction_0001());
		return result;
	}

	LinearEasingFunction GeoSourceJames::LinearEasingFunction_0000()
	{
		if (_linearEasingFunction_0000 != nullptr)
		{
			return _linearEasingFunction_0000;
		}
		return _linearEasingFunction_0000 = _compositor.CreateLinearEasingFunction();
	}

	CubicBezierEasingFunction GeoSourceJames::CubicBezierEasingFunction_0000()
	{
		return _compositor.CreateCubicBezierEasingFunction(float2(0.052F, 0.12F), float2(0.432F, 1));
	}

	CubicBezierEasingFunction GeoSourceJames::CubicBezierEasingFunction_0001()
	{
		return _compositor.CreateCubicBezierEasingFunction(float2(0.453F, 0), float2(0.368F, 1));
	}

	CubicBezierEasingFunction GeoSourceJames::CubicBezierEasingFunction_0002()
	{
		return _compositor.CreateCubicBezierEasingFunction(float2(0.556F, 0), float2(0.274F, 1));
	}

	ExpressionAnimation GeoSourceJames::ExpressionAnimation_0000()
	{
		if (_expressionAnimation_0000 != nullptr)
		{
			return _expressionAnimation_0000;
		}
		auto result = _expressionAnimation_0000 = _compositor.CreateExpressionAnimation();
		result.SetReferenceParameter(L"_", ContainerVisual_0000());
		result.Expression(L"_.Progress");
		return result;
	}


    int32_t GeoSourceJames::Dummy()
    {
        throw hresult_not_implemented();
    }

    void GeoSourceJames::Dummy(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }
}
