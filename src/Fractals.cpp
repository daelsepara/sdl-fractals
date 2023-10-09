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

				std::exit(1);
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

				std::exit(1);
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

				std::exit(1);
			}
		}
	}
}

bool ParseString(std::string arg, char **argv, int i, const char *param, std::string &dst)
{
	// temporary character buffer
	char Buffer[256];

	auto len = std::strlen(param);

	auto result = (!arg.compare(0, len, param) && arg.length() > len);

	if (result)
	{
		// clear buffer
		std::memset(Buffer, 0, 255);
		// copy parameter string into buffer
		std::copy(&argv[i][len], &argv[i][len] + (sizeof(Buffer) - len), Buffer);
		// convert to string
		if (std::strlen(Buffer) > 0)
		{
			dst = std::string(Buffer);
		}
	}

	return result;
}

int main(int argc, char **argv)
{
	std::string parameters_file;

	std::string image_file;

	std::string palette_file;

	if (argc > 1)
	{
		for (auto i = 1; i < argc; i++)
		{
			auto arg = std::string(argv[i]);

			std::transform(arg.begin(), arg.end(), arg.begin(), ::toupper);

			ParseString(arg, argv, i, "/PARAMS=", parameters_file);
			ParseString(arg, argv, i, "/PARAMETERS=", parameters_file);
			ParseString(arg, argv, i, "/IMAGE=", image_file);
			ParseString(arg, argv, i, "/PALETTE=", palette_file);
		}
	}

	if (parameters_file.length() > 0)
	{
		auto parameters = Fractal::Parameters(parameters_file);
		
		std::cerr << "Generating '" << parameters.type << "' fractal" << std::endl;

		if (parameters.type == "mandelbrot")
		{
			auto fractal = Fractal::Mandelbrot(parameters);

			if (image_file.length() > 0)
			{
				fractal.generate(image_file, palette_file);
			}
			else
			{
				fractal.generate(palette_file);
			}
		}
		else if (parameters.type == "mandelbrot2")
		{
			auto fractal = Fractal::Mandelbrot2(parameters);

			if (image_file.length() > 0)
			{
				fractal.generate(image_file, palette_file);
			}
			else
			{
				fractal.generate(palette_file);
			}
		}
		else if (parameters.type == "mandelbrot3")
		{
			auto fractal = Fractal::Mandelbrot3(parameters);

			if (image_file.length() > 0)
			{
				fractal.generate(image_file, palette_file);
			}
			else
			{
				fractal.generate(palette_file);
			}
		}
		else if (parameters.type == "newton1")
		{
			auto fractal = Fractal::Newton1(parameters);

			if (image_file.length() > 0)
			{
				fractal.generate(image_file, palette_file);
			}
			else
			{
				fractal.generate(palette_file);
			}
		}
		else if (parameters.type == "julia")
		{
			auto fractal = Fractal::Julia(parameters);

			if (image_file.length() > 0)
			{
				fractal.generate(image_file, palette_file);
			}
			else
			{
				fractal.generate(palette_file);
			}
		}
		else if (parameters.type == "burningship")
		{
			auto fractal = Fractal::BurningShip(parameters);

			if (image_file.length() > 0)
			{
				fractal.generate(image_file, palette_file);
			}
			else
			{
				fractal.generate(palette_file);
			}
		}
		else if (parameters.type == "tricorn")
		{
			auto fractal = Fractal::Tricorn(parameters);

			if (image_file.length() > 0)
			{
				fractal.generate(image_file, palette_file);
			}
			else
			{
				fractal.generate(palette_file);
			}
		}
		else if (parameters.type == "multicorn")
		{
			auto fractal = Fractal::Multicorn(parameters);

			if (image_file.length() > 0)
			{
				fractal.generate(image_file, palette_file);
			}
			else
			{
				fractal.generate(palette_file);
			}
		}
		else if (parameters.type == "barnsleyfern")
		{
			auto fractal = Fractal::BarnsleyFern(parameters);

			if (image_file.length() > 0)
			{
				fractal.generate(image_file, palette_file);
			}
			else
			{
				fractal.generate(palette_file);
			}
		}
		else
		{
			std::cerr << "Unable to generate unknown '"
					  << parameters.type
					  << "' fractal."
					  << std::endl;
		}
	}

	return 0;
}
