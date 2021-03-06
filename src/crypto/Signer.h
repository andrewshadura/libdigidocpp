/*
 * libdigidocpp
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#pragma once

#include "../Exception.h"

namespace digidoc
{
    class X509Cert;
    class SignerPrivate;
    class EXP_DIGIDOC Signer
    {

      public:
          virtual ~Signer();

          virtual X509Cert cert() const = 0;
          virtual void sign(const std::string &method, const std::vector<unsigned char> &digest,
                            std::vector<unsigned char> &signature) = 0;
          std::vector<unsigned char> sign(const std::string &method, const std::vector<unsigned char> &digest);
          std::string method() const;

          std::string city() const;
          std::string stateOrProvince() const;
          std::string postalCode() const;
          std::string countryName() const;
          std::vector<std::string> signerRoles() const;
          void setSignatureProductionPlace(const std::string &city,
              const std::string &stateOrProvince, const std::string &postalCode, const std::string &countryName);
          void setSignerRoles(const std::vector<std::string>& signerRoles);

      protected:
          Signer();
          void setMethod(const std::string &method);

      private:
          DISABLE_COPY(Signer);
          SignerPrivate *d;

    };
}
