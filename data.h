#ifndef DATA_SIMULATOR_DATA_H
#define DATA_SIMULATOR_DATA_H

#include <string>
#include <vector>

// ��������������
class Data
{
public:
	// ������������ѭ������
	enum Loop {NOLOOP = 0, INNERLOOP, OUTERLOOP};

	Data(const std::string& name, Loop loop = NOLOOP) : m_name(name), m_loop(loop) {}

	virtual ~Data() {}

	// ����ѭ��������������׼����һ��״̬
	virtual bool next() { return false; }

	// ��������ѭ��״̬
	virtual void reset() {}

	// ������������
	virtual std::string data() const = 0;

	// ��ȡ���ݵ��ֶ�����
	const std::string& name() const { return m_name; }

	// ��ȡ������������ѭ������
	Loop loop() const { return m_loop; }

private:
	std::string m_name;
	Loop m_loop;
};

// ������������
typedef std::vector<std::string> Config;

#endif

