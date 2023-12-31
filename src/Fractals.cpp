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

	if (result && len < 256)
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
	bool decomp = false;

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
			else if (arg == "/DECOMP")
			{
				decomp = true;
			}
		}
	}

	if (parameters_file.length() > 0)
	{
		auto parameters = Fractal::Parameters(parameters_file);

		if (palette_file.length() > 0)
		{
			parameters.Palette = palette_file;
		}

		if (normalized_coloring)
		{
			parameters.ColorMode = Fractal::ColorMode::NORMALIZED;
		}

		if (log_coloring)
		{
			parameters.ColorMode = Fractal::ColorMode::LOG;
		}

		if (mod_coloring)
		{
			parameters.ColorMode = Fractal::ColorMode::MODULUS;
		}

		if (histogram_coloring)
		{
			parameters.ColorMode = Fractal::ColorMode::HISTOGRAM;
		}

		if (default_coloring)
		{
			parameters.ColorMode = Fractal::ColorMode::DEFAULT;
		}

		if (decomp)
		{
			parameters.Decomp = true;
		}

		if (invertx)
		{
			parameters.InvertX = true;
		}

		if (inverty)
		{
			parameters.InvertY = true;
		}

		if (invert_colors)
		{
			parameters.InvertColors = true;
		}

		Fractal::Base *fractal;

		if (parameters.Type == "barnsleytree")
		{
			fractal = new Fractal::BarnsleyTree(parameters);
		}
		else if (parameters.Type == "ifs")
		{
			fractal = new Fractal::IteratedFunctionSystem(parameters);
		}
		else if (parameters.Type == "julia")
		{
			fractal = new Fractal::Julia(parameters);
		}
		else if (parameters.Type == "juliafn")
		{
			fractal = new Fractal::JuliaFn(parameters);
		}
		else if (parameters.Type == "julia(f1|f2)")
		{
			fractal = new Fractal::JuliaFn12(parameters);
		}
		else if (parameters.Type == "mandelbrot")
		{
			fractal = new Fractal::Mandelbrot(parameters);
		}
		else if (parameters.Type == "mandelbrot2")
		{
			fractal = new Fractal::Mandelbrot2(parameters);
		}
		else if (parameters.Type == "mandelbrot3")
		{
			fractal = new Fractal::Mandelbrot3(parameters);
		}
		else if (parameters.Type == "mandelbrotfn")
		{
			fractal = new Fractal::MandelbrotFn(parameters);
		}
		else if (parameters.Type == "mandelbrot(f1|f2)")
		{
			fractal = new Fractal::MandelbrotFn12(parameters);
		}
		else if (parameters.Type == "newton")
		{
			fractal = new Fractal::Newton(parameters);
		}
		else if (parameters.Type == "newton1")
		{
			fractal = new Fractal::Newton1(parameters);
		}
		else if (parameters.Type == "tricorn")
		{
			fractal = new Fractal::Tricorn(parameters);
		}
		else
		{
			std::cerr << "Unable to generate unknown '"
					  << parameters.Type
					  << "' fractal."
					  << std::endl;

			return 1;
		}

		if (!benchmark)
		{
			std::cerr << "Generating '" << parameters.Type << "' fractal" << std::endl;

			if (image_file.length() > 0)
			{
				fractal->Save(image_file);
			}
			else
			{
				fractal->Render();
			}
		}
		else
		{
			fractal->Benchmark();
		}
	}

	return 0;
}
