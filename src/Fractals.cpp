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

// SDL2 header in Windows define SDL_main as main that interferes with the build
#ifdef _WIN32
#undef main
#endif

void reset_colormap(Fractal::Parameters &parameters)
{
	parameters.log_coloring = false;
	parameters.normalized_coloring = false;
	parameters.mod_coloring = false;
	parameters.histogram_coloring = false;
}

int main(int argc, char **argv)
{
	std::string parameters_file;

	std::string image_file;

	std::string palette_file;

	// overrides
	bool normalized_coloring = false;
	bool log_coloring = false;
	bool mod_coloring = false;
	bool histogram_coloring = false;
	bool invertx = false;
	bool inverty = false;
	bool benchmark = false;
	bool invert_colors = false;
	bool default_coloring = false;

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

			if (arg == "/LOG")
			{
				log_coloring = true;
			}
			else if (arg == "/NORMALIZED")
			{
				normalized_coloring = true;
			}
			else if (arg == "/MOD")
			{
				mod_coloring = true;
			}
			else if (arg == "/HISTOGRAM")
			{
				histogram_coloring = true;
			}
			else if (arg == "/DEFAULT")
			{
				default_coloring = true;
			}
			else if (arg == "/INVERT")
			{
				invert_colors = true;
			}
			else if (arg == "/INVERTX")
			{
				invertx = true;
			}
			else if (arg == "/INVERTY")
			{
				inverty = true;
			}
			else if (arg == "/BENCHMARK")
			{
				benchmark = true;
			}
		}
	}

	if (parameters_file.length() > 0)
	{
		auto parameters = Fractal::Parameters(parameters_file);

		if (normalized_coloring)
		{
			reset_colormap(parameters);

			parameters.normalized_coloring = true;
		}

		if (log_coloring)
		{
			reset_colormap(parameters);

			parameters.log_coloring = true;
		}

		if (mod_coloring)
		{
			reset_colormap(parameters);

			parameters.mod_coloring = true;
		}

		if (histogram_coloring)
		{
			reset_colormap(parameters);

			parameters.histogram_coloring = true;
		}

		if (default_coloring)
		{
			reset_colormap(parameters);
		}

		if (invertx)
		{
			parameters.invert_x = true;
		}

		if (inverty)
		{
			parameters.invert_y = true;
		}

		if (invert_colors)
		{
			parameters.invert_colors = true;
		}

		Fractal::Base *fractal;

		if (parameters.type == "mandelbrot")
		{
			fractal = new Fractal::Mandelbrot(parameters);
		}
		else if (parameters.type == "mandelbrot2")
		{
			fractal = new Fractal::Mandelbrot2(parameters);
		}
		else if (parameters.type == "mandelbrot3")
		{
			fractal = new Fractal::Mandelbrot3(parameters);
		}
		else if (parameters.type == "newton1")
		{
			fractal = new Fractal::Newton1(parameters);
		}
		else if (parameters.type == "julia")
		{
			fractal = new Fractal::Julia(parameters);
		}
		else if (parameters.type == "burningship")
		{
			fractal = new Fractal::BurningShip(parameters);
		}
		else if (parameters.type == "tricorn")
		{
			fractal = new Fractal::Tricorn(parameters);
		}
		else if (parameters.type == "multicorn")
		{
			fractal = new Fractal::Multicorn(parameters);
		}
		else if (parameters.type == "ifs")
		{
			fractal = new Fractal::IteratedFunctionSystem(parameters);
		}
		else if (parameters.type == "simplejulia")
		{
			fractal = new Fractal::SimpleJulia(parameters);
		}
		else
		{
			std::cerr << "Unable to generate unknown '"
					  << parameters.type
					  << "' fractal."
					  << std::endl;

			return 1;
		}

		if (!benchmark)
		{
			std::cerr << "Generating '" << parameters.type << "' fractal" << std::endl;

			if (image_file.length() > 0)
			{
				fractal->save(image_file, palette_file);
			}
			else
			{
				fractal->render(palette_file);
			}
		}
		else
		{
			fractal->benchmark();
		}
	}

	return 0;
}
