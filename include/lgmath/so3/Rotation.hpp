//////////////////////////////////////////////////////////////////////////////////////////////
/// \file Rotation.hpp
/// \brief Header file for a rotation matrix class.
/// \details Light weight rotation class, intended to be fast, and not to provide
///          unnecessary functionality.
///
/// \author Sean Anderson
//////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////
///
/// A note on EIGEN_MAKE_ALIGNED_OPERATOR_NEW (Sean Anderson, as of May 23, 2013)
/// (also see http://eigen.tuxfamily.org/dox-devel/group__TopicStructHavingEigenMembers.html)
///
/// Fortunately, Eigen::Matrix3d and Eigen::Vector3d are NOT 16-byte vectorizable,
/// therefore this class should not require alignment, and can be used normally in STL.
///
/// To inform others of the issue, classes that include *fixed-size vectorizable Eigen types*,
/// see http://eigen.tuxfamily.org/dox-devel/group__TopicFixedSizeVectorizable.html,
/// must include the above macro! Furthermore, special considerations must be taken if
/// you want to use them in STL containers, such as std::vector or std::map.
/// The macro overloads the dynamic "new" operator so that it generates
/// 16-byte-aligned pointers, this MUST be in the public section of the header!
///
//////////////////////////////////////////////////////////////////////////////////////////////

#ifndef LGM_ROTATION_HPP
#define LGM_ROTATION_HPP

#include <Eigen/Dense>

namespace lgmath {
namespace so3 {

class Rotation
{
 public:

  //////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief Default constructor
  //////////////////////////////////////////////////////////////////////////////////////////////
  Rotation();

  //////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief Copy constructor
  //////////////////////////////////////////////////////////////////////////////////////////////
  Rotation(const Rotation& C);

  //////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief Constructor
  //////////////////////////////////////////////////////////////////////////////////////////////
  Rotation(const Eigen::Matrix3d& C);

  //////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief Constructor. The rotation will be C_ba = vec2rot(aaxis_ab)
  //////////////////////////////////////////////////////////////////////////////////////////////
  Rotation(const Eigen::Vector3d& aaxis_ab, unsigned int numTerms = 0);

  //////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief Constructor. The rotation will be C_ba = vec2rot(aaxis_ab), aaxis_ab must be 3x1
  //////////////////////////////////////////////////////////////////////////////////////////////
  Rotation(const Eigen::VectorXd& aaxis_ab);

  //////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief Destructor
  //////////////////////////////////////////////////////////////////////////////////////////////
  ~Rotation() {}

  //////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief Assignment operator. Note pass-by-value is intentional.
  //////////////////////////////////////////////////////////////////////////////////////////////
  Rotation& operator=(Rotation C);

  //////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief Gets the underlying rotation matrix
  //////////////////////////////////////////////////////////////////////////////////////////////
  const Eigen::Matrix3d& matrix() const;

  //////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief Get the corresponding Lie algebra (axis-angle) using the logarithmic map
  //////////////////////////////////////////////////////////////////////////////////////////////
  Eigen::Vector3d vec() const;

  //////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief Get the inverse (transpose) matrix
  //////////////////////////////////////////////////////////////////////////////////////////////
  Rotation inverse() const;

  //////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief Reproject the rotation matrix back onto SO(3)
  //////////////////////////////////////////////////////////////////////////////////////////////
  void reproject();

  //////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief In-place right-hand side multiply C_rhs
  //////////////////////////////////////////////////////////////////////////////////////////////
  Rotation& operator*=(const Rotation& C_rhs);

  //////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief Right-hand side multiply C_rhs
  //////////////////////////////////////////////////////////////////////////////////////////////
  Rotation operator*(const Rotation& C_rhs) const;

  //////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief In-place right-hand side multiply this matrix by the inverse of C_rhs
  //////////////////////////////////////////////////////////////////////////////////////////////
  Rotation& operator/=(const Rotation& C_rhs);

  //////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief Right-hand side multiply this matrix by the inverse of C_rhs
  //////////////////////////////////////////////////////////////////////////////////////////////
  Rotation operator/(const Rotation& C_rhs) const;

  //////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief Right-hand side multiply this matrix by the point vector p_a
  //////////////////////////////////////////////////////////////////////////////////////////////
  Eigen::Vector3d operator*(const Eigen::Vector3d& p_a) const;

 private:

  //////////////////////////////////////////////////////////////////////////////////////////////
  /// Rotation matrix from a to b
  //////////////////////////////////////////////////////////////////////////////////////////////
  Eigen::Matrix3d C_ba_;

};

} // so3
} // lgmath

//////////////////////////////////////////////////////////////////////////////////////////////
/// \brief print transformation
//////////////////////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& out, const lgmath::so3::Rotation& T);

#endif // LGM_ROTATION_HPP
