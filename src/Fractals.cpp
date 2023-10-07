#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>

#include "FractalTypes.hpp"
#include "Parameters.hpp"
#include "Utilities.hpp"

void ParseInt(std::string arg, const char *str, const char *var, int &dst)
{
	auto len = std::string(str).length();

	if (len > 0)
	{
		if (!arg.compare(0, len, str) && arg.length() > len)
		{
			try
			{
				auto val = std::stoi(arg.substr(len));

				std::cerr << "... " << var << " = " << val << std::endl;

				dst = val;
			}
			catch (const std::invalid_argument &ia)
			{
				std::cerr << "... " << var << " = NaN " << ia.what() << std::endl;
				exit(1);
			}
		}
	}
}

void ParseInts(std::string arg, const char *str, const char *var, std::vector<int> &ints)
{
	auto len = std::string(str).length();

	if (len > 0)
	{
		if (!arg.compare(0, len, str) && arg.length() > len)
		{
			try
			{
				auto s = arg.substr(len);

				std::string delimiter = ",";

				size_t pos = 0;

				while ((pos = s.find(delimiter)) != std::string::npos)
				{

					auto val = std::stoi(s.substr(0, pos));

					ints.push_back(val);

					s.erase(0, pos + delimiter.length());
				}

				if (s.length() > 0)
				{
					auto val = std::stoi(s.substr(0, pos));

					ints.push_back(val);
				}
			}
			catch (const std::invalid_argument &ia)
			{
				std::cerr << "... " << var << " = NaN " << ia.what() << std::endl;

				exit(1);
			}
		}
	}
}

void ParseDouble(std::string arg, const char *str, const char *var, double &dst)
{
	auto len = std::string(str).length();

	if (len > 0)
	{
		if (!arg.compare(0, len, str) && arg.length() > len)
		{
			try
			{
				auto val = std::stod(arg.substr(len));

				std::cerr << "... " << var << " = " << std::scientific << val << std::endl;

				dst = val;
			}
			catch (const std::invalid_argument &ia)
			{
				std::cerr << "... " << var << " = NaN " << ia.what() << std::endl;

				exit(1);
			}
		}
	}
}

int main(int argc, char **argv)
{
	char Buffer[256];

	std::string parameters_file;

	std::string image_file;

	Fractal::Parameters parameters;

	if (argc > 1)
	{
		for (auto i = 1; i < argc; i++)
		{
			std::string arg = argv[i];

			std::transform(arg.begin(), arg.end(), arg.begin(), ::toupper);

			if (!arg.compare(0, 8, "/PARAMS=") && arg.length() > 8)
			{
				std::memset(Buffer, 0, 255);

				std::copy(&argv[i][8], &argv[i][8] + sizeof(Buffer), Buffer);

				if (std::strlen(Buffer) > 0)
				{
					parameters_file = std::string(Buffer);
				}
			}

			if (!arg.compare(0, 7, "/IMAGE=") && arg.length() > 7)
			{
				std::memset(Buffer, 0, 255);

				std::copy(&argv[i][7], &argv[i][7] + sizeof(Buffer), Buffer);

				if (std::strlen(Buffer) > 0)
				{
					image_file = std::string(Buffer);
				}
			}
		}
	}

	if (parameters_file.length() > 0)
	{
		parameters = Fractal::Load(parameters_file);

		std::cerr << "Generating '" << parameters.type << "' fractal" << std::endl;

		if (parameters.type == "mandelbrot")
		{
			auto fractal = Fractal::Mandelbrot();

			fractal.generate(parameters, image_file);
		}
		else if (parameters.type == "mandelbrot2")
		{
			auto fractal = Fractal::Mandelbrot2();

			fractal.generate(parameters, image_file);
		}
		else if (parameters.type == "mandelbrot3")
		{
			auto fractal = Fractal::Mandelbrot3();

			fractal.generate(parameters, image_file);
		}
	}

	return 0;
}
