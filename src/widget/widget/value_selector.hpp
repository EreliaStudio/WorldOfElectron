#pragma once

#include "miscellaneous/widget_redefinition.hpp"

template <typename TType>
class ValueSelector : public spk::Widget
{
private:
	void _onUpdate() override
	{

	}

	void _onGeometryChange() override
	{
		spk::Vector2Int buttonSize = size().y;
		spk::Vector2Int space = spk::Vector2Int(10, 0);
		spk::Vector2Int labelSize = spk::Vector2Int(size().x - buttonSize.x * 2 - space.x * 2, size().y);

		_decrementValueButton->setGeometry(spk::Vector2Int(0, 0), buttonSize);
		_decrementValueButton->setLayer(layer() + 0.01f);
		_valueDisplayer->setGeometry(_decrementValueButton->anchor() + _decrementValueButton->size() * spk::Vector2Int(1, 0) + space, labelSize);
		_valueDisplayer->setLayer(layer() + 0.01f);
		_incrementValueButton->setGeometry(_valueDisplayer->anchor() + _valueDisplayer->size() * spk::Vector2Int(1, 0) + space, buttonSize);
		_incrementValueButton->setLayer(layer() + 0.01f);

	}

	void _onRender() override
	{
		if (_updateValueFontSize == true)
		{
			_valueDisplayer->label().setFontSize(_valueDisplayer->computeOptimalFontSize(0.1f, _padding));

			_updateValueFontSize = false;	
		}
	}

	std::vector<TType> _values;
	size_t _index;
	std::function<std::string(const TType &)> _converterCallback;

	Button *_decrementValueButton;
	Button *_incrementValueButton;
	TextLabel *_valueDisplayer;
	bool _updateValueFontSize;
	spk::Vector2Int _padding;

public:
	ValueSelector(spk::Widget *p_parent) : ValueSelector("Unnamed ValueSelector", p_parent) {}
	ValueSelector(const std::string &p_name, spk::Widget *p_parent) :
		spk::Widget(p_name, p_parent),
		_decrementValueButton(makeChild<Button>(p_name + " - Decrement button", this)),
		_incrementValueButton(makeChild<Button>(p_name + " - Increment button", this)),
		_valueDisplayer(makeChild<TextLabel>(p_name + " - Value Displayer", this)),
		_converterCallback([&](const TType &value) -> std::string
		{
			std::stringstream ss;
			ss << value;
			return ss.str();
		}),
		_index(0)
	{
		setButtonTexts("<", ">");

		_decrementValueButton->activate();
		_decrementValueButton->setOnClickCallback([&]()
		{
			if (_index != 0)
				_index--;
			else
				_index = _values.size() - 1;

			_valueDisplayer->label().setText(_converterCallback != nullptr ? _converterCallback(_values[_index]) : "Invalid converter");
			_updateValueFontSize = true;
		});

		_incrementValueButton->activate();
		_incrementValueButton->setOnClickCallback([&]()
		{
			_index++;
			if (_index == _values.size())
				_index = 0;

			_valueDisplayer->label().setText(_converterCallback != nullptr ? _converterCallback(_values[_index]) : "Invalid converter");
			_updateValueFontSize = true;
		});
		
		_valueDisplayer->label().setVerticalAlignment(spk::VerticalAlignment::Centered);
		_valueDisplayer->label().setHorizontalAlignment(spk::HorizontalAlignment::Centered);
		_valueDisplayer->activate();
	}

	void setCornerSize(const spk::Vector2Int& p_cornerSize)
	{
		_decrementValueButton->box(Button::State::Pressed).setCornerSize(p_cornerSize);
		_decrementValueButton->box(Button::State::Released).setCornerSize(p_cornerSize);

		_incrementValueButton->box(Button::State::Pressed).setCornerSize(p_cornerSize);
		_incrementValueButton->box(Button::State::Released).setCornerSize(p_cornerSize);

		_valueDisplayer->box().setCornerSize(p_cornerSize);
		_updateValueFontSize = true;
	}

	spk::Font::Size computeOptimalFontSize(const float& p_ratio, const spk::Vector2Int& p_padding = 0)
	{
		std::cout << "_decrementValueButton [" << _decrementValueButton->label(Button::State::Pressed).text() << "] : " << _decrementValueButton->computeOptimalFontSize(p_ratio, p_padding).text << std::endl;
		std::cout << "_incrementValueButton [" << _incrementValueButton->label(Button::State::Pressed).text() << "] : " << _incrementValueButton->computeOptimalFontSize(p_ratio, p_padding).text << std::endl;
		spk::Font::Size result = std::min({
			_decrementValueButton->computeOptimalFontSize(p_ratio, p_padding),
			_incrementValueButton->computeOptimalFontSize(p_ratio, p_padding),
		});

		return (result);
	}

	void setFontSize(const spk::Font::Size& p_fontSize)
	{
		_decrementValueButton->label(Button::State::Pressed).setFontSize(p_fontSize);
		_decrementValueButton->label(Button::State::Released).setFontSize(p_fontSize);
		
		_incrementValueButton->label(Button::State::Pressed).setFontSize(p_fontSize);
		_incrementValueButton->label(Button::State::Released).setFontSize(p_fontSize);
	}

	void setValueLabelPadding(const spk::Vector2Int& p_padding)
	{
		_padding = p_padding;
		_updateValueFontSize = true;
	}

	Button *decrementValueButton()
	{
		return (_decrementValueButton);
	}

	Button *incrementValueButton()
	{
		return (_incrementValueButton);
	}

	TextLabel *valueDisplayer()
	{
		return (_valueDisplayer);
	}

	void setButtonTexts(const std::string &p_decrementText, const std::string &p_incrementText)
	{
		_decrementValueButton->label(Button::State::Pressed).setText(p_decrementText);
		_decrementValueButton->label(Button::State::Released).setText(p_decrementText);
		
		_incrementValueButton->label(Button::State::Pressed).setText(p_incrementText);
		_incrementValueButton->label(Button::State::Released).setText(p_incrementText);
	}

	void defineConvertionCallback(const std::function<std::string(const TType &)> &p_callback)
	{
		_converterCallback = p_callback;
	}

	void insertValue(const TType &p_value)
	{
		_values.push_back(p_value);
	}
	void selectValue(const TType &p_value)
	{
		_index = 0;
		while (_index < _values.size() && _values[_index] != p_value)
		{
			_index++;
		}
		_valueDisplayer->label().setText(_converterCallback != nullptr ? _converterCallback(_values[_index]) : "Invalid converter");
		_updateValueFontSize = true;
	}
	void setIndex(const size_t& p_index)
	{
		_index = p_index;
		_valueDisplayer->label().setText(_converterCallback != nullptr ? _converterCallback(_values[_index]) : "Invalid converter");
		_updateValueFontSize = true;
	}
	const TType &value()
	{
		if (_values.size() >= _index)
			throw std::runtime_error("Can't access invalid selected data inside ValueSelector");
		return (_values[_index]);
	}
};