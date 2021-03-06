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

#include "X509Cert.h"

namespace digidoc
{
    /**
     * X.509 certificate store interface.
     */
    class X509CertStorePrivate;
    class X509CertStore
    {
      public:
          static X509CertStore* instance();

          void activate(const std::string &territory) const;
          std::vector<X509Cert> certs() const;
          X509Cert findIssuer(const X509Cert &cert) const;
          bool verify(const X509Cert &cert, time_t *t = nullptr) const;

      private:
          X509CertStore();
          ~X509CertStore();
          DISABLE_COPY(X509CertStore);

          X509CertStorePrivate *d;
    };
}
