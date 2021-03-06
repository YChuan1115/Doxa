// Δoxa Binarization Framework
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#ifndef TRSINGH_HPP
#define TRSINGH_HPP

#include "Algorithm.hpp"
#include "LocalWindow.hpp"
#include "MeanCalculator.hpp"


namespace Doxa
{
	/// <summary>
	/// The T.R. Singh Algorithm: T. Romen Singh, Sudipta Roy, O. Imocha Singh, Tejmani Sinam, Kh. Manglem Singh
	/// </summary>
	/// <remarks>"A New local Adaptive Thresholding Technique in Binarization", 2011.</remarks>
	class TRSingh : public Algorithm<TRSingh>, public MeanCalculator
	{
	public:
		void Initialize(const Image& grayScaleImageIn)
		{
			Algorithm::Initialize(grayScaleImageIn);
			MeanCalculator::Initialize(grayScaleImageIn);
		}

		void ToBinary(Image& binaryImageOut, const Parameters& parameters)
		{
			double mean;

			// Read parameters, utilizing defaults
			const int windowSize = parameters.Get("window", 75);
			const double k = parameters.Get("k", 0.2);

			LocalWindow::Process(binaryImageOut, Algorithm::grayScaleImageIn, windowSize, [&](const Region& window, const int& position) {
				CalculateMean(mean, window);
				const double meandev = (double)Algorithm::grayScaleImageIn.data[position] - mean;

				return mean * (1 + k * ((meandev / (1 - meandev + std::numeric_limits<double>::lowest())) - 1));
			});
		}
	};
}


#endif //TRSINGH_HPP
