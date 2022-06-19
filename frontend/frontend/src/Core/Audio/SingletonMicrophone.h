#pragma once
class SingletonMicrophone{
private:
	static std::shared_ptr<Microphone> microphone;
	SingletonMicrophone();
public:
	template <class ...Arg>
	static void Set(Arg ...arg) {
		microphone = std::make_shared<Microphone>(arg...);
	}

	static std::shared_ptr<Microphone> Get() {
		if (microphone == nullptr) {
			throw std::logic_error("先にSetを実行してください");
			return nullptr;
		}
		return microphone;
	}
};


