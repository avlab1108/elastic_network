/**
 * @file eigen_spectra_task.h
 * @brief This file contains @ref eigen_spectra_task class.
 * @author Minas Hovhannisyan
 */

#pragma once

#include <base_task.h>

/**
 * @class eigen_spectra_task
 * @brief Calculates eigenvalues spectra.
 */
class eigen_spectra_task : public base_task
{
public:
  /**
   * @brief Base interface override.
   * @return Execution status.
   */
  virtual int execute() override;
};
