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

#include "SignatureBES.h"


namespace digidoc
{

namespace xades { class OCSPRefType; class UnsignedSignaturePropertiesType; }

class SignatureTM: public SignatureBES
{
public:
    SignatureTM(unsigned int id, BDoc *bdoc);
    SignatureTM(std::istream &sigdata, BDoc *bdoc);
    virtual ~SignatureTM();

    std::vector<unsigned char> nonce() const;
    X509Cert OCSPCertificate() const;
    std::string producedAt() const;
    virtual void validate(Validate params = ValidateFULL) const;
    virtual void extendTo(const std::string &profile);

protected:
    void addCertificateValue(const std::string& certId, const X509Cert& x509);
    std::vector<unsigned char> getOCSPResponseValue() const;
    virtual std::string realTime() const;
    xades::UnsignedSignaturePropertiesType& unsignedSignatureProperties() const;

private:
    DISABLE_COPY(SignatureTM);

    void addOid(std::vector<unsigned char> &digest, const std::string &uri) const;
    std::string nonceAlgorithm() const;

    void setOCSPResponseValue(const std::vector<unsigned char>& data);
};

}
