#include"Value.h"
#include"utils.h"

const Value Value::operator+(const Value& v) const
	{
	if (v.type == none_t) {
		return *this;
	}

	Value newValue;
	if (type == v.type) {
		newValue.type = type;
		switch (type)
			{
		case string_t:
			newValue.stringVal = this->stringVal + v.stringVal;
			break;
		case number_t:
			newValue.numberVal = this->numberVal + v.numberVal;
			break;
		case bool_t:
			newValue.boolVal = this->boolVal + v.boolVal;
			break;
			default:
				break;
			}
	}
	else {
		if (type == string_t) {
			newValue.type = string_t;
			string str;
			if (v.type == number_t) {
				str = toStr(v.numberVal);
			}
			else if (v.type == bool_t) {
				str = v.boolVal ? "true" : "false";
			}
			newValue.stringVal = stringVal + str;
		}
		else if (type == number_t) {
			if (v.type == string_t) {
				newValue.type = string_t;
				newValue.stringVal = toStr(numberVal) + v.stringVal;
			}
			else if (v.type == bool_t) {
				newValue.type = number_t;
				int temp = v.boolVal ? 1 : 0;
				newValue.numberVal = numberVal + temp;
			}
		}
		else if (type == bool_t) {

			if (v.type == string_t) {
				newValue.type = string_t;
				string str = boolVal ? "true" : "false";
				newValue.stringVal =  str + v.stringVal;
			}
			else if (v.type == number_t) {
				int temp = boolVal ? 1 : 0;
				newValue.type = number_t;
				newValue.numberVal = v.numberVal + temp;
			}
		}
	}

		return newValue;
	}

const Value Value::operator-(const Value& v) const
{
	if (v.type == none_t) {
		return *this;
	}

	Value newValue;
	if (type == v.type) {
		newValue.type = type;
		switch (type)
		{
		case string_t:
			newValue.type = none_t;
			break;
		case number_t:
			newValue.numberVal = this->numberVal - v.numberVal;
			break;
		case bool_t:
			newValue.boolVal = this->boolVal - v.boolVal;
			break;
		default:
			break;
		}
	}
	else {
		newValue.type = none_t;
	}

	return newValue;
}

const Value Value::operator*(const Value& v) const
{
	if (v.type == none_t) {
		return *this;
	}

	Value newValue;
	if (type == v.type) {
		newValue.type = type;
		switch (type)
		{
		case string_t:
			newValue.type = none_t;
			break;
		case number_t:
			newValue.numberVal = this->numberVal * v.numberVal;
			break;
		case bool_t:
			newValue.boolVal = this->boolVal * v.boolVal;
			break;
		default:
			break;
		}
	}
	else {
		newValue.type = none_t;
	}

	return newValue;
}

const Value Value::operator/(const Value& v) const
{
	if (v.type == none_t) {
		return *this;
	}

	Value newValue;
	if (type == v.type) {
		newValue.type = type;
		switch (type)
		{
		case string_t:
			newValue.type = none_t;
			break;
		case number_t:
			newValue.numberVal = this->numberVal / v.numberVal;
			break;
		case bool_t:
			if (v.boolVal == false) newValue.type = none_t;
			else newValue.boolVal = this->boolVal / v.boolVal;
			break;
		default:
			break;
		}
	}
	else {
		newValue.type = none_t;
	}

	return newValue;
}

const Value Value::operator&&(const Value& v)const {
	Value newValue;
	if (type == bool_t && v.type == bool_t) {
		newValue.type = bool_t;
		newValue.boolVal = boolVal && v.boolVal;
	}

	return newValue;
}


const Value Value::operator||(const Value& v)const {
		Value newValue;
		if (type == bool_t && v.type == bool_t) {
			newValue.type = bool_t;
			newValue.boolVal = boolVal || v.boolVal;
		}

		return newValue;
};

bool Value::operator<(const Value& v)const {
	if (type == v.type) {
		switch (type)
		{
		case none_t:
			break;
		case string_t:
			return stringVal < v.stringVal;
			break;
		case number_t:
			return numberVal < v.numberVal;
			break;
		case bool_t:
			return boolVal < v.boolVal;
			break;
		default:
			break;
		}
	}
	return false;
}

bool Value::operator>(const Value& v)const {
	if (type == v.type) {
		switch (type)
		{
		case none_t:
			break;
		case string_t:
			return stringVal > v.stringVal;
			break;
		case number_t:
			return numberVal > v.numberVal;
			break;
		case bool_t:
			return boolVal > v.boolVal;
			break;
		default:
			break;
		}
	}
	return false;
}

bool Value::operator>=(const Value& v)const {
	if (type == v.type) {
		return  !(this->operator<(v));
	}
	return false;
}

bool Value::operator<=(const Value& v)const {
	if (type == v.type) {
		return  !(this->operator>(v));
	}
	return false;
}

bool Value::operator==(const Value& v)const {
	if (type == v.type) {
		switch (type)
		{
		case none_t:
			break;
		case string_t:
			return stringVal == v.stringVal;
			break;
		case number_t:
			return numberVal == v.numberVal;
			break;
		case bool_t:
			return boolVal == v.boolVal;
			break;
		default:
			break;
		}
	}
	return false;
}

bool Value::operator!=(const Value& v) const {
	if (type == v.type) {
		return !(this->operator==(v));
	}
	return true;
}

const Value& Value::operator!() {
	if (type == bool_t) {
		boolVal = !boolVal;
	}
	else {
		type = bool_t;
		boolVal = false;
	}

	return *this;
}

ostream& operator<<(ostream& os,const Value& v) {
	switch (v.type)	
	{
	case string_t:
		os <<v.stringVal;
		break;
	case number_t:
		os << v.numberVal;
		break;
	case bool_t: 
	{
		string str = v.boolVal ? "true" : "false";
		os << str;
	}
		break;
	case none_t:
		os << "NaN";
		break;
	default:
		break;
	}

	return os;
}